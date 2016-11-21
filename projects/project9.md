---
title: Vantage Point calculations and database, part 2
layout: lecture
mathjax: true
---

This is work needed after milestone 2.

In part 1 you created a database with 20 binary tree indexes, and accessed it from the command line.

In this part you will front it with a multi-threaded socket server.

(1). If you have completed it, replace the unbalanced binary tree database by a red black one. The subsequent steps should not care if the underlying database is unbalanced binary-tree or red-black tree, so that provides you a path to move forward in-case you are having issues with the red-black-tree database (which is hard!)

(2). replace your command line client program with one that keeps the same interface but communicates with the server over a socket. You must now support two possible queries: (a) compute the closest from a time-series which is in the database (the argument here is the id) (b) compute the distance from a timeseries provided and thus shipped over the wire to the server. One complication in this second scenario is that calculating the distance of an incoming timeseries against the vantage points now needs to happen on the server. Earlier it happened in the process which used the database as a library. This will slow down your IO (the GIL) but we shall let it be.

(3). You will need to develop a protocol to communicate between client and server, and set up the sockets.

Here is an example of such a protocol. Feel free to ignore any of this below and develop your own (likely simpler) protocol. This is meant to be an example of a future-extensible protocol:

```python
import json

LENGTH_FIELD_LENGTH = 4


def serialize(json_obj):
    '''Turn a JSON object into bytes suitable for writing out to the network.
    Includes a fixed-width length field to simplify reconstruction on the other
    end of the wire.'''
    #your code here



class Deserializer(object):
    '''A buffering and bytes-to-json engine.
    Data can be received in arbitrary chunks of bytes, and we need a way to
    reconstruct variable-length JSON objects from that interface. This class
    buffers up bytes until it can detect that it has a full JSON object (via
    a length field pulled off the wire). To use this, shove bytes in with the
    append() function and call ready() to check if we've reconstructed a JSON
    object. If True, then call deserialize to return it. That object will be
    removed from this buffer after it is returned.'''

    def __init__(self):
        self.buf = b''
        self.buflen = -1

    def append(self, data):
        self.buf += data
        self._maybe_set_length()

    def _maybe_set_length(self):
        if self.buflen < 0 and len(self.buf) >= LENGTH_FIELD_LENGTH:
            self.buflen = int.from_bytes(self.buf[0:LENGTH_FIELD_LENGTH], byteorder="little")

    def ready(self):
        return (self.buflen > 0 and len(self.buf) >= self.buflen)

    def deserialize(self):
        json_str = self.buf[LENGTH_FIELD_LENGTH:self.buflen].decode()
        self.buf = self.buf[self.buflen:]
        self.buflen = -1
        # There may be more data in the buffer already, so preserve it
        self._maybe_set_length()
        try:
            #Note how now everything is assumed to be an OrderedDict
            obj = json.loads(json_str)
            #print("OBJ", obj)
            return obj
        except json.JSONDecodeError:
            print('Invalid JSON object received:\n'+str(json_str))
            return None
```

error handling:

```python
import enum

class TSDBError(Exception):
    pass

class TSDBOperationError(Exception):
    pass

class TSDBConnectionError(Exception):
    pass

class TSDBStatus(enum.IntEnum):
    OK = 0
    UNKNOWN_ERROR = 1
    INVALID_OPERATION = 2
    INVALID_KEY = 3
    INVALID_COMPONENT = 4
    PYPE_ERROR = 5

    @staticmethod
    def encoded_length():
        return 3

    def encode(self):
        return str.encode('{:3d}'.format(self.value))

    @classmethod
    def from_bytes(cls, data):
        return cls(int(data.decode()))
```



and here is an example of what this JSON might look like:

```python
import timeseries as ts
#you will have to come up with an error handling system
from .tsdb_error import *


# Interface classes for TSDB network operations.
# These are a little clunky (extensibility is meh), but it does provide strong
# typing for TSDB ops and a straightforward mechanism for conversion to/from
# JSON objects.


class TSDBOp(dict):
    def __init__(self, op):
        self['op'] = op

    def to_json(self, obj=None):
        # This is both an interface function and its own helper function.
        # It recursively converts elements in a hierarchical data structure
        # into a JSON-encodable form. It does *not* handle class instances
        # unless they have a 'to_json' method.
        #print(">>>",self.items())
        if obj is None:
            obj = self
        json_dict = {}
        if isinstance(obj, str) or not hasattr(obj, '__len__') or obj is None:
            return obj
        for k, v in obj.items():
            if isinstance(v, str) or not hasattr(v, '__len__') or v is None:
                json_dict[k] = v
            elif isinstance(v, TSDBStatus):
                json_dict[k] = v.name
            elif isinstance(v, list):
                json_dict[k] = [self.to_json(i) for i in v]
            elif isinstance(v, dict):
                json_dict[k] = self.to_json(v)
            elif hasattr(v, 'to_json'):
                json_dict[k] = v.to_json()
            else:
                raise TypeError('Cannot convert object to JSON: '+str(v))
        return json_dict

    @classmethod
    def from_json(cls, json_dict):
        if 'op' not in json_dict:
            raise TypeError('Not a TSDB Operation: '+str(json_dict))
        if json_dict['op'] not in typemap:
            raise TypeError('Invalid TSDB Operation: '+str(json_dict['op']))
        return typemap[json_dict['op']].from_json(json_dict)


class TSDBOp_withTS(TSDBOp):
    def __init__(self, ts):
        super().__init__('with_ts')
        self['ts'] = ts

    @classmethod
    def from_json(cls, json_dict):
        return cls(ts.TimeSeries(*(json_dict['ts'])))


class TSDBOp_Return(TSDBOp):

    def __init__(self, status, op, payload=None):
        super().__init__(op)
        self['status'], self['payload'] = status, payload

    @classmethod
    def from_json(cls, json_dict):  #should not be used, this is to return to client
        return cls(json_dict['status'], json_dict['payload'])

class TSDBOp_withID(TSDBOp):
    def __init__(self, idee):
        super().__init__('with_id')
        self['id'] = idee

    @classmethod
    def from_json(cls, json_dict):
        return cls(json_dict['id'])




# This simplifies reconstructing TSDBOp instances from network data.
typemap = {
  'with_ts': TSDBOp_withTS,
  'with_id': TSDBOp_withID,
}
```

The kernel of the server might then look a bit like this:

```python
#get it on the socket, then (perhaps in a thread)
def data_received(self, data):
        self.deserializer.append(data)
        if self.deserializer.ready():
            msg = self.deserializer.deserialize()
            status = TSDBStatus.OK  # until proven otherwise.
            response = TSDBOp_Return(status, None)  # until proven otherwise.
            try:
                tsdbop = TSDBOp.from_json(msg)
            except TypeError as e:
                response = TSDBOp_Return(TSDBStatus.INVALID_OPERATION, None)
            if status is TSDBStatus.OK:
                if isinstance(op, TSDBOp_withTS):
                    response = self._with_ts(tsdbop)
                elif isinstance(op, TSDBOp_withID):
                    response = self._with_id(tsdbop)
                else:
                    response = TSDBOp_Return(TSDBStatus.UNKNOWN_ERROR, tsdbop['op'])

            serialize(response.to_json())
            #send it out
```



You can choose between the below two electives. The extra-credit is only if you want more points and are having too much fun..

EXTRA CREDIT 1:

But since python has the GIL, this will block any other IO from happening. Thus let us run all distance calculations in processes.
Thus, let each thread in the server have access to a co-processor pool (see http://chimera.labs.oreilly.com/books/1230000000393/ch12.html#_discussion_204) and note you will have to hand the two time series (one the incoming and two the one from the db) over to a process in this pool.

EXTRA CREDIT 1: even more credit

Now, take your code to insert a time series and to create a vantage point and encapsulate these into functions which can be run in threads as well. Each new time series insertion should trigger a process that computes its distance to all vantage points. This should happen in the process pool. (Similarly each new vantage point insertion should trigger computing distances to all time series and these two operations should not happen simultaneously. We will, for simplicity in this project, assume that only the initial vantage points are allowed.)

OR

EXTRA CREDIT 2:

Extend the interface in the client program to embed a lispy (stupidlang can be used as a base for this) query language which allows for similarity queries on our database.

EXTRA CREDIT 2: even more credit

Extend your query language to allow filtering queries on postgres metadata (test metadata will be provided in `project10.html`)
We wont combine these as such queries will be slow in the the binary search tree database. But its worth it for you to think of how you might combine them in one database.


