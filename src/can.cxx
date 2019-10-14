/* can.cxx
 *
 * Copyright (C) 2014 Michael Martens
*/

#include "can.h"
#include <structmember.h>

TCanMessage::TCanMessage()
{
  PyObject_Init((PyObject*) this, &TCanMessage::oType);

#ifdef UNDER_CE
  msg.dwLen = 0;
  msg.dwID = 0;
  pDataBuffer = PyBuffer_FromReadWriteMemory(msg.pData, 8);
#else
  msg.ID = 0;
  msg.MSGTYPE = PCAN_MESSAGE_STANDARD;
  msg.LEN = 0;
  pDataBuffer = PyBuffer_FromReadWriteMemory(msg.DATA, 8);
#endif
}

TCanMessage::~TCanMessage()
{
  Py_DECREF(pDataBuffer);
}


PyMemberDef TCanMessage::members[] = {
  {NULL}  /* Sentinel */
};

PyMethodDef TCanMessage::methods[] = {
    {NULL}  /* Sentinel */
};

PyGetSetDef TCanMessage::getsets[] = {
  {"ID", (getter)TCanMessage::PyGetId, (setter)TCanMessage::PySetId, "Id", NULL},
  {"TYPE", (getter)TCanMessage::PyGetType, (setter)TCanMessage::PySetType, "Type", NULL},
  {"LEN", (getter)TCanMessage::PyGetLen, (setter)TCanMessage::PySetLen, "Length", NULL},
  {"DATA", (getter)TCanMessage::PyGetData, (setter)TCanMessage::PySetData, "Data", NULL},
  {NULL}  /* Sentinel */
};

PyObject* TCanMessage::PyGetId(TCanMessage* self, void* vp)
{
#ifdef UNDER_CE
  return PyInt_FromLong(self->msg.dwID & 0x1fffffff);
#else
  return PyInt_FromLong(self->msg.ID);
#endif
}

int TCanMessage::PySetId(TCanMessage* self, PyObject* arg, void* vp)
{
  if(PyInt_Check(arg))
  {
#ifdef UNDER_CE
    self->msg.dwID = (self->msg.dwID & ~0x1fffffff) | PyInt_AsLong(arg);
#else
    self->msg.ID = PyInt_AsLong(arg);
#endif
    return 0;
  }

  PyErr_SetString(PyExc_TypeError, "Integer expected");
  return -1;
}


PyObject* TCanMessage::PyGetType(TCanMessage* self, void* vp)
{
#ifdef UNDER_CE
  return PyInt_FromLong(self->msg.dwID & ~0x1FFFFFFF ? CAN_MSGTYPE_EXTENDED : CAN_MSGTYPE_STANDARD);
#else
  return PyInt_FromLong(self->msg.MSGTYPE);
#endif
}

int TCanMessage::PySetType(TCanMessage* self, PyObject* arg, void* vp)
{
  if(PyInt_Check(arg))
  {
#ifdef UNDER_CE
    if(PyInt_AsLong(arg) == CAN_MSGTYPE_EXTENDED)
    {
      self->msg.dwID |= 0x40000000;
    }
    else
    {
      self->msg.dwID &= ~0x40000000;
    }
#else
    self->msg.MSGTYPE = PyInt_AsLong(arg);
#endif
    return 0;
  }

  PyErr_SetString(PyExc_TypeError, "Integer expected");
  return -1;
}

PyObject* TCanMessage::PyGetLen(TCanMessage* self, void* vp)
{
#ifdef UNDER_CE
  return PyInt_FromLong(self->msg.dwLen);
#else
  return PyInt_FromLong(self->msg.LEN);
#endif
}

int TCanMessage::PySetLen(TCanMessage* self, PyObject* arg, void* vp)
{
  if(PyInt_Check(arg))
  {
#ifdef UNDER_CE
    self->msg.dwLen = PyInt_AsLong(arg);
#else
    self->msg.LEN = PyInt_AsLong(arg);
#endif
    return 0;
  }

  PyErr_SetString(PyExc_TypeError, "Integer expected");
  return -1;
}

PyObject* TCanMessage::PyGetData(TCanMessage* self, void* vp)
{
  TCanMessageData* pData;
  try
  {
#ifdef UNDER_CE
    pData = new TCanMessageData(self, self->msg.pData);
#else
    pData = new TCanMessageData(self, self->msg.DATA);
#endif
  }
  catch(TXArgument)
  {
    PyErr_SetString(PyExc_TypeError, "Bad Can Data");
    return NULL;
  }
  return (PyObject*)pData;
}

int TCanMessage::PySetData(TCanMessage* self, PyObject* arg, void* vp)
{
#ifdef UNDER_CE
  PyErr_SetString(PyExc_TypeError, "Read Only");
#else
  PyErr_SetString(PyExc_TypeError, "Read Only");
#endif
  return -1;
}


int TCanMessage::Init(TCanMessage *self, PyObject *args, PyObject *kwds)
{
  return 0;
}

PyObject* TCanMessage::New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  PyObject* obj = type->tp_alloc(type, 0);

  return obj; 
}

PyObject* TCanMessage::Alloc(PyTypeObject *self, Py_ssize_t nitems)
{
  TCanMessage* obj;

  try
  {  
    obj = new TCanMessage();
  }
  catch(TXAlloc)
  {
    return PyErr_NoMemory();
  }

  return (PyObject*)obj;
}

void TCanMessage::Dealloc(TCanMessage* self)
{
  self->ob_type->tp_free(self);
}

void TCanMessage::Free(TCanMessage* self)
{
  delete self;
}



PyTypeObject TCanMessage::oType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "TCanMessage",                  /*tp_name*/
    sizeof(TCanMessage),           /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)TCanMessage::Dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "CAN Message Object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    TCanMessage::methods,          /* tp_methods */
    TCanMessage::members,          /* tp_members */
    TCanMessage::getsets,          /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)TCanMessage::Init,   /* tp_init */
    (allocfunc)TCanMessage::Alloc, /* tp_alloc */
    (newfunc)TCanMessage::New,     /* tp_new */
    (freefunc)TCanMessage::Free,   /* tp_free */
};


TCanMessageData::TCanMessageData(TCanMessage* pMsg, BYTE* pData)
{
  PyObject_Init((PyObject*) this, &TCanMessageData::oType);
  
  if(pMsg == NULL || pData == NULL)
    throw TXArgument();

  this->pMsg = pMsg;
  Py_INCREF(this->pMsg);
  
#ifdef UNDER_CE
  this->pData = pMsg->msg.pData;
#else
  this->pData = pMsg->msg.DATA;
#endif
}

TCanMessageData::~TCanMessageData()
{
  Py_DECREF(this->pMsg);
}


PyMemberDef TCanMessageData::members[] = {
  {NULL}  /* Sentinel */
};

PyMethodDef TCanMessageData::methods[] = {
    {NULL}  /* Sentinel */
};

PyGetSetDef TCanMessageData::getsets[] = {
  {NULL}  /* Sentinel */
};

PySequenceMethods TCanMessageData::sequencemethods[] = {
  {
    (lenfunc)PySequence_Size,               // lenfunc sq_length 
    0,                                      // binaryfunc sq_concat 
    0,                                      // ssizeargfunc sq_repeat 
    (ssizeargfunc)PySequence_GetItem,       // ssizeargfunc sq_item
    (ssizessizeargfunc)PySequence_GetSlice, // ssizessizeargfunc sq_slice
    (ssizeobjargproc)PySequence_SetItem,    // ssizeobjargproc sq_ass_item
    0,                  // ssizessizeobjargproc sq_ass_slice
    0,                  // objobjproc sq_contains 
    0,                  // binaryfunc sq_inplace_concat 
    0,                  // ssizeargfuncs sq_inplace_repeat
  },
};


Py_ssize_t TCanMessageData::PySequence_Size(TCanMessageData* self)
{
  return 8;
}

PyObject* TCanMessageData::PySequence_GetItem(TCanMessageData* self, Py_ssize_t i)
{
  if(i >= 8) return NULL;
  return PyInt_FromLong(self->pData[i]);
}

int TCanMessageData::PySequence_SetItem(TCanMessageData* self, Py_ssize_t i, PyObject *v)
{
  BYTE value;
  value = (BYTE)PyInt_AsLong(v);

  if(i >= 8) return -1;
  self->pData[i] = value;

  return 0;
}

PyObject* TCanMessageData::PySequence_GetSlice(TCanMessageData* self, Py_ssize_t i1, Py_ssize_t i2)
{
  int i;
  int len;
  PyObject* pObj;

  if(i1 >= 8) return NULL;
  if(i2 >= 8) return NULL;

  len = i2 - i1;
  pObj = PyTuple_New(len);
  for(i=0 ; i< len ; i++)
  {
    PyTuple_SetItem(pObj, i, PyInt_FromLong(self->pData[i1 + i]));
  }
  return pObj;
}

int TCanMessageData::Init(TCanMessageData *self, PyObject *args, PyObject *kwds)
{
  return 0;
}

PyObject* TCanMessageData::New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  PyObject* obj = type->tp_alloc(type, 0);

  return obj; 
}

PyObject* TCanMessageData::Alloc(PyTypeObject *self, Py_ssize_t nitems)
{
  TCanMessageData* obj;

  try
  {  
    obj = new TCanMessageData(NULL, NULL);
  }
  catch(TXAlloc)
  {
    return PyErr_NoMemory();
  }
  catch(TXArgument)
  {
    return PyErr_NoMemory();
  }

  return (PyObject*)obj;
}

void TCanMessageData::Dealloc(TCanMessageData* self)
{
  self->ob_type->tp_free(self);
}

void TCanMessageData::Free(TCanMessageData* self)
{
  delete self;
}



PyTypeObject TCanMessageData::oType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "TCanMessageData",                  /*tp_name*/
    sizeof(TCanMessageData),           /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)TCanMessageData::Dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    TCanMessageData::sequencemethods,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "CAN Message Data",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    TCanMessageData::methods,          /* tp_methods */
    TCanMessageData::members,          /* tp_members */
    TCanMessageData::getsets,          /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)TCanMessageData::Init,   /* tp_init */
    (allocfunc)TCanMessageData::Alloc, /* tp_alloc */
    (newfunc)TCanMessageData::New,     /* tp_new */
    (freefunc)TCanMessageData::Free,   /* tp_free */
};



TCanFilter::TCanFilter()
{
  PyObject_Init((PyObject*) this, &TCanFilter::oType);
#ifdef UNDER_CE
  pFilter = NULL; //new tCANFilter[nrFilter];
  iNum = 0; //nrFilter;
#else

#endif
}

TCanFilter::~TCanFilter()
{
#ifdef UNDER_CE
  if(pFilter)
    delete[] pFilter;
#else

#endif
}

PyMemberDef TCanFilter::members[] = {
  {NULL}  /* Sentinel */
};

PyMethodDef TCanFilter::methods[] = {
  {"SetFilter", (PyCFunction)TCanFilter::PySetFilter, METH_VARARGS, "Set Filter"},
  {NULL}  /* Sentinel */
};

PyGetSetDef TCanFilter::getsets[] = {
  {NULL}  /* Sentinel */
};


PyObject* TCanFilter::PySetFilter(TCanFilter* self, PyObject* args)
{
  unsigned long index;
  unsigned long dwId;
  unsigned long bType;
  unsigned long dwMask;

  if (! PyArg_ParseTuple(args, "kkkk", &index, &dwId, &bType, &dwMask))
    return NULL;

#ifdef UNDER_CE
  if(index >= self->iNum)
  {
    PyErr_SetString(PyExc_IndexError, "Invalid Index");
    return NULL;
  }

  if(bType == CAN_MSGTYPE_EXTENDED)
  {
    self->pFilter[index].dwAcc = dwId | 0x40000000;
  }
  else
  {
    self->pFilter[index].dwAcc = dwId & ~0x40000000;
  }
  self->pFilter[index].dwMask = dwMask;
#else

#endif
  Py_INCREF(Py_None);
  return Py_None;
}

int TCanFilter::Init(TCanFilter *self, PyObject *args, PyObject *kwds)
{
  int iNum = 0;

  if (! PyArg_ParseTuple(args, "i", &iNum))
    return -1;

#ifdef UNDER_CE
  if(self->pFilter)
    delete[] self->pFilter;
  self->pFilter = new tCANFilter[iNum];
  self->iNum = iNum;
#else

#endif
  return 0;
}

PyObject* TCanFilter::New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  PyObject* obj = type->tp_alloc(type, 0);

  return obj; 
}

PyObject* TCanFilter::Alloc(PyTypeObject *self, Py_ssize_t nitems)
{
  TCanFilter* obj;

  try
  {  
    obj = new TCanFilter();
  }
  catch(TXAlloc)
  {
    return PyErr_NoMemory();
  }

  return (PyObject*)obj;
}

void TCanFilter::Dealloc(TCanFilter* self)
{
  self->ob_type->tp_free(self);
}

void TCanFilter::Free(TCanFilter* self)
{
  delete self;
}



PyTypeObject TCanFilter::oType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "TCanFilter",                  /*tp_name*/
    sizeof(TCanFilter),           /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)TCanFilter::Dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "CAN Filter Object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    TCanFilter::methods,          /* tp_methods */
    TCanFilter::members,          /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)TCanFilter::Init,   /* tp_init */
    (allocfunc)TCanFilter::Alloc, /* tp_alloc */
    (newfunc)TCanFilter::New,     /* tp_new */
    (freefunc)TCanFilter::Free,   /* tp_free */
};



TCanInterface::TCanInterface()
{
  PyObject_Init((PyObject*) this, &TCanInterface::oType);
#ifdef UNDER_CE
  hDevice = 0;
  hCandevDll = 0;
  hOpenCANDevice = 0;
  hCloseCANDevice = 0;
  hSendCANMsg = 0;
  hGetCANMsg = 0;
  hSetCANDeviceReceiveEvent = 0;
  hSetCANDeviceFilter = 0;
#else
  hChannel = PCAN_USBBUS1;
  iChannelStatus = PCAN_ERROR_INITIALIZE; 
#endif

  hCANReceiveThread = 0;
  
  hCANReceiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if(hCANReceiveEvent == NULL)
  {
    throw TXAlloc();
  }

  hThreadExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  if(hThreadExitEvent == NULL)
  {
    throw TXAlloc();
  }

  Py_INCREF(Py_None);
  pReceiveHandler = Py_None;
  
  pParentThreadState = NULL;
}

TCanInterface::~TCanInterface()
{
  DWORD dwExitCode;
  SetEvent(hThreadExitEvent);
  do
  {
    GetExitCodeThread(hCANReceiveThread, &dwExitCode);
  }
  while(dwExitCode == STILL_ACTIVE);

  Close();
  Py_DECREF(pReceiveHandler);
}

int TCanInterface::Open()
{
#ifdef UNDER_CE
  hCandevDll = LoadLibrary(L"CANDEV");
  if(hCandevDll == NULL)
  {
    throw TXInit();
  }

  hOpenCANDevice = (HANDLE (*)(DWORD))GetProcAddress(hCandevDll, L"OpenCANDevice"); // 2
  if(hOpenCANDevice == NULL) throw TXInit();

  hCloseCANDevice = (BOOL (*)(HANDLE))GetProcAddress(hCandevDll, L"CloseCANDevice"); // 0
  if(hCloseCANDevice == NULL) throw TXInit();

  hSendCANMsg = (BOOL (*)(HANDLE, tCANMsg*))GetProcAddress(hCandevDll, L"SendCANMsg"); // 3
  if(hSendCANMsg == NULL) throw TXInit();

  hGetCANMsg = (BOOL (*)(HANDLE, tCANMsg*))GetProcAddress(hCandevDll, L"GetCANMsg"); // 1
  if(hGetCANMsg == NULL) throw TXInit();

  hSetCANDeviceReceiveEvent = (BOOL (*)(HANDLE, HANDLE))GetProcAddress(hCandevDll, L"SetCANDeviceReceiveEvent"); // 5
  if(hSetCANDeviceReceiveEvent == NULL) throw TXInit();

  hSetCANDeviceFilter = (BOOL (*)(HANDLE, int, tCANFilter*))GetProcAddress(hCandevDll, L"SetCANDeviceFilter"); // 4
  if(hSetCANDeviceFilter == NULL) throw TXInit();

  hDevice = hOpenCANDevice(0);
  if(hDevice == INVALID_HANDLE_VALUE)
  {
    throw TXInit();
  }
  
#else
  iChannelStatus = CAN_Initialize(hChannel, PCAN_BAUD_250K, 0, 0, 0); 
  if(iChannelStatus != PCAN_ERROR_OK)
  {
    throw TXInit();
  }
#endif
  return 0;
}

int TCanInterface::Close()
{
#ifdef UNDER_CE
  if(hDevice == 0)
    return 0;
  hCloseCANDevice(hDevice);

  FreeLibrary(hCandevDll);

  hDevice = 0;
  hCandevDll = 0;
  hOpenCANDevice = 0;
  hCloseCANDevice = 0;
  hSendCANMsg = 0;
  hGetCANMsg = 0;
  hSetCANDeviceReceiveEvent = 0;
  hSetCANDeviceFilter = 0;
#else
  if(iChannelStatus != PCAN_ERROR_OK)
    return 0;

  CAN_Uninitialize(hChannel);
  iChannelStatus = PCAN_ERROR_INITIALIZE;
#endif
  return 0;
}

int TCanInterface::SetReceiveEvent(HANDLE hEvent)
{
#ifdef UNDER_CE
  if(!hSetCANDeviceReceiveEvent(hDevice, hEvent))
    return -1;
#else
  if(iChannelStatus != PCAN_ERROR_OK)
    return -1;
  if(CAN_SetValue(hChannel, PCAN_RECEIVE_EVENT, &hEvent, sizeof(HANDLE)) != PCAN_ERROR_OK)
    return -1;
#endif
  return 0;
}

DWORD WINAPI TCanInterface::CANReceiveThreadFunc(LPVOID pvSelf)
{
  TCanInterface* self;
  HANDLE hEvent[2];
  DWORD dwWaitResult;
  TCanMessage tReceiveMsg;
  PyThreadState * myThreadState;
  
  self = (TCanInterface*)pvSelf;

  PyEval_AcquireLock();
  myThreadState = PyThreadState_New(self->pParentThreadState->interp);
  PyThreadState_Swap(myThreadState);

  hEvent[0] = self->hCANReceiveEvent;
  hEvent[1] = self->hThreadExitEvent;

  self->SetReceiveEvent(self->hCANReceiveEvent);

//  PySys_WriteStdout("CANReceiveThreadFunc started");

  while(1)
  {
    PyThreadState_Swap(NULL);
    PyEval_ReleaseLock();

    dwWaitResult = WaitForMultipleObjects(2, hEvent, FALSE, INFINITE);

    PyEval_AcquireLock();
    PyThreadState_Swap(myThreadState);
    
//    PySys_WriteStdout("CANReceiveThreadFunc received message");
    
    if(dwWaitResult == WAIT_OBJECT_0)
    {
      if(PyCallable_Check(self->pReceiveHandler))
      {
        PyObject_CallObject(self->pReceiveHandler, NULL);
      }

      continue; 
    }

    if(dwWaitResult == WAIT_OBJECT_0 + 1) break;
    
    if(dwWaitResult == WAIT_FAILED) break;

  }
  
  PyThreadState_Swap(NULL);
  PyThreadState_Clear(myThreadState);
  PyThreadState_Delete(myThreadState);
  PyEval_ReleaseLock();

  self->SetReceiveEvent(NULL);
  ExitThread(0);
  return 0;
}

PyMemberDef TCanInterface::members[] = {
  {"ReceiveHandler", T_OBJECT_EX, offsetof(TCanInterface, pReceiveHandler), 0, "Receive Handler"},
  {NULL}  /* Sentinel */
};

PyMethodDef TCanInterface::methods[] = {
  {"Open", (PyCFunction)TCanInterface::PyOpen, METH_VARARGS, "Open"},
  {"Close", (PyCFunction)TCanInterface::PyClose, METH_VARARGS, "Close"},
  {"Read", (PyCFunction)TCanInterface::PyRead, METH_VARARGS, "Read"},
  {"Write", (PyCFunction)TCanInterface::PyWrite, METH_VARARGS, "Write"},
  {"Start", (PyCFunction)TCanInterface::PyStart, METH_VARARGS, "Start"},
  {"Stop", (PyCFunction)TCanInterface::PyStop, METH_VARARGS, "Stop"},
  {"SetFilter", (PyCFunction)TCanInterface::PySetFilter, METH_VARARGS, "Set Filter"},
  {NULL}  /* Sentinel */
};

PyGetSetDef TCanInterface::getsets[] = {
  {NULL}  /* Sentinel */
};

PyObject* TCanInterface::PyOpen(TCanInterface* self, PyObject* args)
{

#ifdef UNDER_CE
  self->hCandevDll = LoadLibrary(L"CANDEV");
  if(self->hCandevDll == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hOpenCANDevice = (HANDLE (*)(DWORD))GetProcAddress(self->hCandevDll, L"OpenCANDevice"); // 2
  if(self->hOpenCANDevice == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hCloseCANDevice = (BOOL (*)(HANDLE))GetProcAddress(self->hCandevDll, L"CloseCANDevice"); // 0
  if(self->hCloseCANDevice == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hSendCANMsg = (BOOL (*)(HANDLE, tCANMsg*))GetProcAddress(self->hCandevDll, L"SendCANMsg"); // 3
  if(self->hSendCANMsg == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hGetCANMsg = (BOOL (*)(HANDLE, tCANMsg*))GetProcAddress(self->hCandevDll, L"GetCANMsg"); // 1
  if(self->hGetCANMsg == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hSetCANDeviceReceiveEvent = (BOOL (*)(HANDLE, HANDLE))GetProcAddress(self->hCandevDll, L"SetCANDeviceReceiveEvent"); // 5
  if(self->hSetCANDeviceReceiveEvent == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hSetCANDeviceFilter = (BOOL (*)(HANDLE, int, tCANFilter*))GetProcAddress(self->hCandevDll, L"SetCANDeviceFilter"); // 4
  if(self->hSetCANDeviceFilter == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }

  self->hDevice = self->hOpenCANDevice(0);
  if(self->hDevice == INVALID_HANDLE_VALUE)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }
  
#else
  self->iChannelStatus = CAN_Initialize(self->hChannel, PCAN_BAUD_250K, 0, 0, 0); 
  if(self->iChannelStatus != PCAN_ERROR_OK)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Error");
    return NULL;
  }
#endif
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* TCanInterface::PyClose(TCanInterface* self, PyObject* args)
{
#ifdef UNDER_CE
  self->hCloseCANDevice(self->hDevice);

  FreeLibrary(self->hCandevDll);

  self->hDevice = 0;
  self->hCandevDll = 0;
  self->hOpenCANDevice = 0;
  self->hCloseCANDevice = 0;
  self->hSendCANMsg = 0;
  self->hGetCANMsg = 0;
  self->hSetCANDeviceReceiveEvent = 0;
  self->hSetCANDeviceFilter = 0;
#else
  if(self->iChannelStatus == PCAN_ERROR_OK)
  {
    CAN_Uninitialize(self->hChannel);
    self->iChannelStatus = PCAN_ERROR_INITIALIZE;
  }
#endif
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* TCanInterface::PyRead(TCanInterface* self, PyObject* args)
{
  TCanMessage* msg;

  if (! PyArg_ParseTuple(args, "O!", &TCanMessage::oType, (PyObject*)&msg))
    return NULL;
    
#ifdef UNDER_CE
  if(!self->hGetCANMsg(self->hDevice, &(msg->msg)))
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
#else
  if(self->iChannelStatus != PCAN_ERROR_OK || CAN_Read(self->hChannel, &(msg->msg), NULL) != PCAN_ERROR_OK)
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
#endif
  Py_INCREF(Py_True);
  return Py_True;
}

PyObject* TCanInterface::PyWrite(TCanInterface* self, PyObject* args)
{
  TCanMessage* msg;

  if (! PyArg_ParseTuple(args, "O!", &TCanMessage::oType, (PyObject*)&msg))
    return NULL;
  
#ifdef UNDER_CE
  if(!self->hSendCANMsg(self->hDevice, &(msg->msg)))
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
#else
  if(self->iChannelStatus != PCAN_ERROR_OK || CAN_Write(self->hChannel, &(msg->msg)) != PCAN_ERROR_OK)
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
#endif
  Py_INCREF(Py_True);
  return Py_True;
}

PyObject* TCanInterface::PyStart(TCanInterface* self, PyObject* args)
{   
  DWORD dwThreadId;
  PyThreadState *_save;
  
  _save = PyThreadState_Swap(NULL);
  PyEval_ReleaseLock();

  self->pParentThreadState = _save;
  self->hCANReceiveThread = CreateThread(NULL, 0, CANReceiveThreadFunc, (LPVOID)self, 0, &dwThreadId);
  if(self->hCANReceiveThread == NULL)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Start Thread Error");
    return NULL;
  }

  PyEval_AcquireLock();
  PyThreadState_Swap(_save);
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* TCanInterface::PyStop(TCanInterface* self, PyObject* args)
{
  DWORD dwExitCode;
  PyThreadState *_save;
  
  _save = PyThreadState_Swap(NULL);
  PyEval_ReleaseLock();

  SetEvent(self->hThreadExitEvent);
  do
  {
    GetExitCodeThread(self->hCANReceiveThread, &dwExitCode);
  }
  while(dwExitCode == STILL_ACTIVE);

  PyEval_AcquireLock();
  PyThreadState_Swap(_save);

  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* TCanInterface::PySetFilter(TCanInterface* self, PyObject* args)
{
  TCanFilter* pFilter;
  
  if (! PyArg_ParseTuple(args, "O!", &TCanFilter::oType, (PyObject*)&pFilter))
    return NULL;
  
#ifdef UNDER_CE
  if(!self->hSetCANDeviceFilter(self->hDevice, pFilter->iNum, pFilter->pFilter))
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface SetFilter Error");
    return NULL;
  }
#else

#endif
  Py_INCREF(Py_None);
  return Py_None;
}

int TCanInterface::Init(TCanInterface *self, PyObject *args, PyObject *kwds)
{ 
  try
  {
    self->Open();
  }
  catch(TXInit)
  {
    PyErr_SetString(PyExc_IOError, "CAN Interface Open Error");
    return -1;
  }

  Py_DECREF(self->pReceiveHandler);
  Py_INCREF(Py_None);
  self->pReceiveHandler = Py_None;

  return 0;
}

PyObject* TCanInterface::New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  PyObject* obj = type->tp_alloc(type, 0);

  return obj; 
}

PyObject* TCanInterface::Alloc(PyTypeObject *self, Py_ssize_t nitems)
{
  TCanInterface* obj;

  try
  {  
    obj = new TCanInterface();
  }
  catch(TXAlloc)
  {
    return PyErr_NoMemory();
  }

  return (PyObject*)obj;
}

void TCanInterface::Dealloc(TCanInterface* self)
{
  self->ob_type->tp_free(self);
}

void TCanInterface::Free(TCanInterface* self)
{
  delete self;
}


PyTypeObject TCanInterface::oType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "TCanInterface",                  /*tp_name*/
    sizeof(TCanInterface),           /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)TCanInterface::Dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "CAN Interface Object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    TCanInterface::methods,          /* tp_methods */
    TCanInterface::members,          /* tp_members */
    TCanInterface::getsets,          /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)TCanInterface::Init,   /* tp_init */
    (allocfunc)TCanInterface::Alloc, /* tp_alloc */
    (newfunc)TCanInterface::New,     /* tp_new */
    (freefunc)TCanInterface::Free,   /* tp_free */
};

