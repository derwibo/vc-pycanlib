/* candll.cxx
 *
 * Copyright (C) 2014 Michael Martens
 */

#include <Python.h>
#include <windows.h>
#include "candll.h"
#include "can.h"


BOOL WINAPI DllMain(HINSTANCE hinstDLL,	DWORD fdwReason, LPVOID lpvReserved)
{
  if(fdwReason == DLL_PROCESS_ATTACH)
  {

  }
  return TRUE;
}

PyMethodDef CanLibMethods[] = {
  {NULL}  /* Sentinel */
};

PyMODINIT_FUNC initcanlib(void)
{
  PyObject *m;

  m = Py_InitModule("canlib", CanLibMethods);
  if (m == NULL)
    return;

  if(PyType_Ready(&TCanInterface::oType) == 0)
    PyModule_AddObject(m, "TCanInterface", (PyObject*) &TCanInterface::oType);
    
  if(PyType_Ready(&TCanMessage::oType) == 0)
    PyModule_AddObject(m, "TCanMessage", (PyObject*) &TCanMessage::oType);
  
  PyType_Ready(&TCanMessageData::oType);
  
  if(PyType_Ready(&TCanFilter::oType) == 0)
    PyModule_AddObject(m, "TCanFilter", (PyObject*) &TCanFilter::oType);
  
  PyModule_AddObject(m, "CAN_MESSAGE_STANDARD", PyInt_FromLong(0x00000000));
  PyModule_AddObject(m, "CAN_MESSAGE_RTR"     , PyInt_FromLong(0x20000000));
  PyModule_AddObject(m, "CAN_MESSAGE_EXTENDED", PyInt_FromLong(0x40000000));
  PyModule_AddObject(m, "CAN_MESSAGE_STATUS"  , PyInt_FromLong(0x80000000));

}
