/*
title : 파이썬 C 연동 테스트
author : ysoftman
desc : 파이썬 C Api 를 사용하여 파이쎤 <-> C 간 함수 호출
python version : 3.5
reference :
https://docs.python.org/3/c-api/index.html
https://docs.python.org/3/extending/index.html#extending-index

[윈도우 경우]
프로젝트 설정 -> c/c++ -> 추가 포함 디렉토리 -> c:\Python35\include  추가
프로젝트 설정 -> linker -> 추가 라이브러리 디렉토리 -> C:\Python35\libs 추가
c:\Python35\python35.dll -> 프로젝트 경로 복사
*/

// Python.h 에 stdio.h stdlib.h string.h 등 기본적인 헤더 파일이 포함되어 있음
#include <Python.h>

static PyObject *MyError;

static PyObject *execute_system_command(PyObject *self, PyObject *args)
{
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	printf("%s\n", command);

	sts = system(command);
	if (sts < 0)
	{
		PyErr_SetString(MyError, "System command failed");
		return NULL;
	}

	return PyLong_FromLong(sts);
}

// 메소드 테이블 설정
static PyMethodDef MyMethods[] = {

	// 파이썬에서 systcmd 를 호출하면 실제 execute_system_command 가 실행되도록 함
	{"syscmd", execute_system_command, METH_VARARGS, "Execute a shell command."},
	{NULL, NULL, 0, NULL} /* Sentinel */
};

// 모듈 구조 설정
static struct PyModuleDef MyModule = {
	PyModuleDef_HEAD_INIT,
	"MyModule", /* name of module */
	NULL,		/* module documentation, may be NULL */
	-1,			/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
	MyMethods};

// 모듈 초기화 함수
// 파이썬에서 import 시 맨 처음 호출된다.
// 초기화 함수는 PyInit_이름() 형식으로 만들어야 한다
PyMODINIT_FUNC PyInit_MyModule(void)
{
	return PyModule_Create(&MyModule);
}

int main(int argc, char *argv[])
{
	printf("%s testing...\n", argv[0]);

	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
	if (program == NULL)
	{
		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
		exit(1);
	}
	/* Add a built-in module, before Py_Initialize */
	PyImport_AppendInittab("MyModule", PyInit_MyModule);

	/* Pass argv[0] to the Python interpreter */
	Py_SetProgramName(program);

	/* Initialize the Python interpreter.  Required. */
	Py_Initialize();

	PyMem_RawFree(program);

	//Py_Finalize();

	return 0;
}
