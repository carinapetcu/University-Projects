#include <stdio.h>
#include "tests.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	do_all_tests();

	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	UI* ui = createUI(service);
	start_application(ui);
	destroyUI(ui);

	_CrtDumpMemoryLeaks();
	return 0;
}