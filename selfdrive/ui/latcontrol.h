#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CAPTURE_STATE_NONE 0
#define CAPTURE_STATE_CAPTURING 1


bool screen_button_clicked(int touch_x, int touch_y) {
  if (touch_x >= 1660 && touch_x <= 1810) {
    if (touch_y >= 885 && touch_y <= 1035) {
      return true;
    }
  }
  return false;
}

static void screen_draw_button(UIState *s, int touch_x, int touch_y) {
  int btn_w = 150;
  int btn_h = 150;
  int btn_x = 1920 - btn_w;
  int btn_y = 1080 - btn_h;
  nvgBeginPath(s->vg);
  nvgRoundedRect(s->vg, btn_x-110, btn_y-45, btn_w, btn_h, 100);
  nvgStrokeColor(s->vg, nvgRGBA(255,255,255,80));
  nvgStrokeWidth(s->vg, 6);
  nvgStroke(s->vg);

  nvgFontSize(s->vg, 60);
  if (captureState == CAPTURE_STATE_CAPTURING) {
    NVGcolor fillColor = nvgRGBA(255,0,0,150);
    nvgFillColor(s->vg, fillColor);
    nvgFill(s->vg);
    nvgFillColor(s->vg, nvgRGBA(255,255,255,200));
  } else {
      nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 200));
  }
  nvgText(s->vg,btn_x-38,btn_y+50,"REC",NULL);
}

bool latcontrol( UIState *s, int touch_x, int touch_y ) {

  bool touched = false;
  
  screen_draw_button(s, touch_x, touch_y);

  if (screen_button_clicked(touch_x,touch_y)) {}

  if (screen_lock_button_clicked(touch_x,touch_y,lock_button)) {
    screen_toggle_lock();
    touched = true;
  }
  
  return touched;
}
