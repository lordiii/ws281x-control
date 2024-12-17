﻿#ifndef DISPLAY_H
#define DISPLAY_H

#define DSP_BLACK 0x0000
#define DSP_WHITE 0xFFFF
#define DSP_RED 0xF800
#define DSP_GREEN 0x07E0
#define DSP_BLUE 0x001F
#define DSP_CYAN 0x07FF
#define DSP_MAGENTA 0xF81F
#define DSP_YELLOW 0xFFE0
#define DSP_ORANGE 0xFC00

struct DSP_Page;

enum DSP_ELEMENT_TYPE {
    TEXT,
    BTN
};

typedef struct DSP_Text {
    const char *text;
    unsigned short color;
} DSP_Text;

typedef struct DSP_Btn {
    bool active;
    DSP_Text text;

    void (*onClick)(DSP_Btn *btn);
} DSP_Btn;

typedef union DSP_Element_Data {
    DSP_Text text;
    DSP_Btn btn;
} DSP_Element_Data;

typedef struct DSP_Element {
    DSP_Element_Data data;
    DSP_ELEMENT_TYPE type;
} DSP_Element;

typedef struct DSP_Page {
    DSP_Text title;
    DSP_Element *elements;
    unsigned char count;
} DSP_Page;

typedef struct DSP_State {
    short height;
    short width;

    short currentX;
    short currentY;

    DSP_Page *currentPage;

    DSP_Btn **currentButtons;
    unsigned char btnCount;
} DSP_State;

void DSP_init();

void DSP_onButtonMainMenuClick(DSP_Btn *btn);

void DSP_onEffectBtnClick(DSP_Btn *btn);

void DSP_onEffectMenuClick(DSP_Btn *btn);

void DSP_renderText(DSP_Text *text);

void DSP_renderButton(DSP_Btn *btn);

void DSP_onButtonRebootClick(DSP_Btn *btn);

void DSP_renderPage(DSP_Page *page);


void DSP_nextButton(signed char dir);

void DSP_selectButton();


#endif