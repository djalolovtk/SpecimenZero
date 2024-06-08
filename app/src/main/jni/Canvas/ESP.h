#ifndef ESP_H
#define ESP_H

#include <jni.h>
#include "StructsCommon.h"

class ESP {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    ESP() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    ESP(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }

    void DrawText(Color color, const char *txt, Vector2 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 _env->NewStringUTF(txt), pos.X, pos.Y, size);
        }
    }
	
    void DrawName(Color color, float stroke, std::string str, Vector3 pos, float size) {
        
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawName",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.x, pos.y, size);
        }
    }
    
    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, radius);
        }
    }

	void DrawCircle(Color color,float stroke, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                     "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke, pos.X, pos.Y, radius);
        }
    }

    void DrawHorizontalHealthBar(Vector2 screenPos, float width, float maxHealth, float currentHealth) {
        screenPos -= Vector2(0.0f, 8.0f);
        DrawBox(Color(0, 0, 0, 255), 3, Rect(screenPos.X, screenPos.Y, width + 2, 5.0f));
        screenPos += Vector2(1.0f, 1.0f);
        Color clr = Color(0, 255, 0, 255);
        float hpWidth = (currentHealth * width) / maxHealth;
        if (currentHealth <= (maxHealth * 0.6)) {
            clr = Color(255, 255, 0, 255);
        }
        if (currentHealth < (maxHealth * 0.3)) {
            clr = Color(255, 0, 0, 255);
        }
        DrawBox(clr, 3, Rect(screenPos.X, screenPos.Y, hpWidth, 3.0f));
    }

    void DrawVerticalHealth(Vector2 end, float h, float health) {

        float x = end.X;
        float y = end.Y;
        h = -h;

        Color clr = Color(0, 255, 0, 255);

        float hpwidth = h-h*health/100;

        if (health <= (100 * 0.6)) {
            clr = Color(255, 255, 0, 255);
        }
        if (health < (100 * 0.3)) {
            clr = Color(255, 0, 0, 255);
        }

        Rect hpbar((x+h/4)-8,y,4.0f,-h);
        Rect hp((x+h/4)-8,y-hpwidth,2.0f,-h+hpwidth);

        DrawBox(Color(0,0,0,255), 3, hpbar);

        DrawBox(clr,3, hp);

    }

    void DrawCrosshair(Color clr, Vector2 center, float size = 20) {
        float x = center.X - (size / 2.0f);
        float y = center.Y - (size / 2.0f);
        DrawLine(clr, 3, Vector2(x, center.Y), Vector2(x + size, center.Y));
        DrawLine(clr, 3, Vector2(center.X, y), Vector2(center.X, y + size));
    }
    
    void DrawRect(Color color, float stroke, Vector2 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawrect = _env->GetMethodID(canvasView, "DrawRect",
                                                           "(Landroid/graphics/Canvas;IIIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, stroke, pos.X, pos.Y, width, height);
        }
    }
    
	void DrawBox(Color color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.x, rect.y);
        Vector2 v2 = Vector2(rect.x + rect.width, rect.y);
        Vector2 v3 = Vector2(rect.x + rect.width, rect.y + rect.height);
        Vector2 v4 = Vector2(rect.x, rect.y + rect.height);

        DrawLine(color, stroke, v1, v2);
        DrawLine(color, stroke, v2, v3);
        DrawLine(color, stroke, v3, v4);
        DrawLine(color, stroke, v4, v1);
    }
    
	void DrawFilledBox(Color color, Rect rect) {
         if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID gayp = _env->GetMethodID(canvasView, "DrawFilledRect",
                                                           "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, gayp, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, rect.x, rect.y, rect.width, rect.height);
        }
    }
};

#endif
