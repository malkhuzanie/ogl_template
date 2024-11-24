#include <entity.h>

struct Clock : public Entity {
  void render() {
    drawClockFace();
    drawClockHands();
  }

  void drawCircle(float x, float y, float radius, int segments, bool filled) {
    if (filled) {
      glBegin(GL_TRIANGLE_FAN);
      glVertex2f(x, y);
      for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
      }
      glEnd();
    } else {
      glBegin(GL_LINE_LOOP);
      for (int i = 0; i < segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
      }
      glEnd();
    }
  }

  void drawClockFace() {
    // Soft cream background
    glColor3f(0.96f, 0.95f, 0.88f);
    drawCircle(0, 0, 0.9f, 100, true);

    // Dark border
    glColor3f(0.2f, 0.2f, 0.3f);
    glLineWidth(5.0f);
    drawCircle(0, 0, 0.9f, 100, false);

    // Minute markers
    for (int i = 0; i < 60; i++) {
      float angle = i * 6.0f * M_PI / 180.0f - M_PI / 2;
      float start_radius = (i % 5 == 0) ? 0.8f : 0.85f;
      float end_radius = 0.9f;

      glLineWidth(i % 5 == 0 ? 3.0f : 1.0f);
      glColor3f(0.2f, 0.2f, 0.3f);

      glBegin(GL_LINES);
      glVertex2f(start_radius * cos(angle), start_radius * sin(angle));
      glVertex2f(end_radius * cos(angle), end_radius * sin(angle));
      glEnd();
    }
  }

  void drawClockHands() {
    // Get current time
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    // Hour hand
    float hourAngle = (timeinfo->tm_hour % 12 + timeinfo->tm_min / 60.0f) *
                          30.0f * M_PI / 180.0f -
                      M_PI / 2.0f;
    glColor3f(0.1f, 0.1f, 0.3f);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f * cos(hourAngle), 0.5f * sin(hourAngle));
    glEnd();

    // Minute hand
    float minuteAngle =
        (timeinfo->tm_min + timeinfo->tm_sec / 60.0f) * 6.0f * M_PI / 180.0f -
        M_PI / 2.0f;
    glColor3f(0.3f, 0.3f, 0.5f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.7f * cos(minuteAngle), 0.7f * sin(minuteAngle));
    glEnd();

    // Second hand (CORRECTED)
    //
    float secondAngle =
        (60 - timeinfo->tm_sec) * 6.0f * M_PI / 180.0f - M_PI / 2.0f;
    glColor3f(0.8f, 0.2f, 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.75f * cos(secondAngle), 0.75f * sin(secondAngle));
    glEnd();

    // Center dot
    glColor3f(0.1f, 0.1f, 0.3f);
    drawCircle(0, 0, 0.02f, 20, true);
  }
};
