/* can.h
 *
 * Copyright (C) 2014 Michael Martens
*/

#ifndef CAN_H
#define CAN_H

#include <Python.h>
#include <windows.h>

#ifdef UNDER_CE

#include "candevice.h"

#define CAN_MSGTYPE_STANDARD 0x00
#define CAN_MSGTYPE_EXTENDED 0x02

#else

#include "PCANBasic.h"

#define CAN_MSGTYPE_STANDARD 0x00
#define CAN_MSGTYPE_EXTENDED 0x02

#endif

class TCanInterface;

class TCanMessage
{
  public:
    PyObject_HEAD

  private:
#ifdef UNDER_CE
    tCANMsg msg;
#else
    TPCANMsg msg;
#endif
    PyObject* pDataBuffer;
  public:
    TCanMessage();
    ~TCanMessage();

    class TXAlloc { };
    class TXArgument{ };

    static PyMemberDef members[];
    static PyMethodDef methods[];
    static PyGetSetDef getsets[];

    static PyObject* PyGetId(TCanMessage* self, void*);
    static int PySetId(TCanMessage* self, PyObject* arg, void*);

    static PyObject* PyGetType(TCanMessage* self, void*);
    static int PySetType(TCanMessage* self, PyObject* arg, void*);

    static PyObject* PyGetLen(TCanMessage* self, void*);
    static int PySetLen(TCanMessage* self, PyObject* arg, void*);

    static PyObject* PyGetData(TCanMessage* self, void*);
    static int PySetData(TCanMessage* self, PyObject* arg, void*);

    static int Init(TCanMessage *self, PyObject *args, PyObject *kwds);
    static PyObject* New(PyTypeObject *type, PyObject *args, PyObject *kwds);
    static PyObject* Alloc(PyTypeObject *self, Py_ssize_t nitems);
    static void Dealloc(TCanMessage* self);
    static void Free(TCanMessage* self);

    static PyTypeObject oType;

  friend class TCanInterface;
  friend class TCanMessageData;
};

class TCanMessageData
{
  public:
    PyObject_HEAD

  private:
    TCanMessage* pMsg;
    BYTE* pData;
  public:
    TCanMessageData(TCanMessage* pMsg, BYTE* pData);
    ~TCanMessageData();

    class TXAlloc { };
    class TXArgument{ };

    static PyMemberDef members[];
    static PyMethodDef methods[];
    static PyGetSetDef getsets[];
    static PySequenceMethods sequencemethods[];

    static Py_ssize_t PySequence_Size(TCanMessageData* self);
    static PyObject* PySequence_GetItem(TCanMessageData* self, Py_ssize_t i);
    static int PySequence_SetItem(TCanMessageData* self, Py_ssize_t i, PyObject* v);
    static PyObject* PySequence_GetSlice(TCanMessageData* self, Py_ssize_t i1, Py_ssize_t i2);

    static int Init(TCanMessageData* self, PyObject *args, PyObject *kwds);
    static PyObject* New(PyTypeObject *type, PyObject *args, PyObject *kwds);
    static PyObject* Alloc(PyTypeObject *self, Py_ssize_t nitems);
    static void Dealloc(TCanMessageData* self);
    static void Free(TCanMessageData* self);

    static PyTypeObject oType;
};

class TCanFilter
{
  public:
    PyObject_HEAD

  private:
#ifdef UNDER_CE
    int iNum;
    tCANFilter* pFilter;
#else
 
#endif    
  public:
    TCanFilter();
    ~TCanFilter();

    class TXAlloc { };
    class TXArgument{ };

    static PyMemberDef members[];
    static PyMethodDef methods[];
    static PyGetSetDef getsets[];

    static PyObject* PySetFilter(TCanFilter* self, PyObject* args);

    static int Init(TCanFilter *self, PyObject *args, PyObject *kwds);
    static PyObject* New(PyTypeObject *type, PyObject *args, PyObject *kwds);
    static PyObject* Alloc(PyTypeObject *self, Py_ssize_t nitems);
    static void Dealloc(TCanFilter* self);
    static void Free(TCanFilter* self);

    static PyTypeObject oType;

  friend class TCanInterface;
};

class TCanInterface
{
  public:
    PyObject_HEAD

  private:
#ifdef UNDER_CE
    HANDLE hDevice;
    HINSTANCE hCandevDll;
    
    HANDLE (*hOpenCANDevice)(DWORD);
    BOOL (*hCloseCANDevice)(HANDLE);
    BOOL (*hSendCANMsg)(HANDLE, tCANMsg*);
    BOOL (*hGetCANMsg)(HANDLE, tCANMsg*);
    BOOL (*hSetCANDeviceReceiveEvent)(HANDLE, HANDLE);
    BOOL (*hSetCANDeviceFilter)(HANDLE, int, tCANFilter*);

#else
    TPCANHandle hChannel;
    TPCANStatus iChannelStatus;
#endif

    HANDLE hCANReceiveEvent;
    HANDLE hThreadExitEvent;

    static DWORD WINAPI CANReceiveThreadFunc( LPVOID );
    HANDLE hCANReceiveThread;
    PyThreadState* pParentThreadState;

    PyObject* pReceiveHandler;

  public:
    TCanInterface();
    ~TCanInterface();

    class TXAlloc { };
    class TXInit { };
    class TXArgument{ };
    
    int Open();
    int Close();
    int SetReceiveEvent(HANDLE hEvent);
    
    static PyMemberDef members[];
    static PyMethodDef methods[];
    static PyGetSetDef getsets[];

    static PyObject* PyOpen(TCanInterface* self, PyObject* args);
    static PyObject* PyClose(TCanInterface* self, PyObject* args);
    static PyObject* PyRead(TCanInterface* self, PyObject* args);
    static PyObject* PyWrite(TCanInterface* self, PyObject* args);
    static PyObject* PyStart(TCanInterface* self, PyObject* args);
    static PyObject* PyStop(TCanInterface* self, PyObject* args);
    static PyObject* PySetFilter(TCanInterface* self, PyObject* args);

    static int Init(TCanInterface *self, PyObject *args, PyObject *kwds);
    static PyObject* New(PyTypeObject *type, PyObject *args, PyObject *kwds);
    static PyObject* Alloc(PyTypeObject *self, Py_ssize_t nitems);
    static void Dealloc(TCanInterface* self);
    static void Free(TCanInterface* self);

    static PyTypeObject oType;

};

#endif // CAN_H
