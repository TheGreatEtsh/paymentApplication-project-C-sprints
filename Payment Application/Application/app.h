#ifndef APP_H
#define APP_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void Menu();
void GoBackOrExit();
void ExitProject();
void appStart(void);
void userStory(void);

#endif // !APP_H
