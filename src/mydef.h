/*
 * common.h
 *
 *  Created on: 2020-8-7
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_


#define LRESULT	int
#define MSG_MAINWIN_KEYDOWN         0x001B
#define MSG_MAINWIN_KEYUP           0x001C
#define MSG_MAINWIN_KEYLONGPRESS    0x001D
#define MSG_MAINWIN_KEYALWAYSPRESS  0x001E
#define MSG_MAINWIN_KEYUP_LONG      0x001F

MG_EXPORT int GUIAPI UnregisterIMEWindow (HWND hWnd);

MG_EXPORT int GUIAPI RegisterMainWindow (HWND hWnd);

MG_EXPORT int GUIAPI UnregisterMainWindow (HWND hWnd);

MG_EXPORT void GUIAPI EnableKeyMessage(void);

MG_EXPORT void GUIAPI DisableKeyMessage(void);

#define KEY_UP_FUNC       SCANCODE_CURSORBLOCKUP
#define KEY_DOWN_FUNC     SCANCODE_CURSORBLOCKDOWN
#define KEY_LEFT_FUNC     SCANCODE_CURSORBLOCKLEFT
#define KEY_RIGHT_FUNC    SCANCODE_CURSORBLOCKRIGHT
#define KEY_EXIT_FUNC     SCANCODE_B
#define KEY_ENTER_FUNC    SCANCODE_A

#endif /* COMMON_H_ */
