#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

// Helper function for text drawing with better visibility
void drawText(int x, int y, const char* text, int color = WHITE) {
    setcolor(color);
    outtextxy(x, y, const_cast<char*>(text));
}

class GUI {
private:
    int left, top, right, bottom;
    char str[80];
    
    char* graphicsInput(int x, int y, int maxLength = 10) {
        char input[80] = "";
        int index = 0;
        char ch;
        bool inputting = true;
        int blink_counter = 0;
        bool cursor_visible = true;
        
        // Create input box with contrasting colors
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(x, y, x + maxLength*10, y + 25);
        setcolor(WHITE);
        rectangle(x, y, x + maxLength*10, y + 25);
        
        // Initial cursor
        setcolor(LIGHTGREEN);
        line(x + 5, y + 20, x + 13, y + 20);
        
        while(inputting && index < maxLength) {
            if(kbhit()) {
                ch = getch();
                
                if(ch == 13) { // Enter key
                    inputting = false;
                }
                else if(ch == 8 && index > 0) { // Backspace
                    index--;
                    input[index] = '\0';
                    
                    // Clear previous character
                    setfillstyle(SOLID_FILL, DARKGRAY);
                    bar(x + 5 + index*8, y + 5, x + 13 + index*8, y + 22);
                    
                    // Redraw cursor
                    setcolor(LIGHTGREEN);
                    line(x + 5 + index*8, y + 20, x + 13 + index*8, y + 20);
                }
                else if(ch >= ' ' && ch <= '~' && index < maxLength) {
                    input[index] = ch;
                    setcolor(WHITE);
                    char temp[2] = {ch, '\0'};
                    outtextxy(x + 5 + index*8, y + 5, temp);
                    line(x + 13 + index*8, y + 20, x + 21 + index*8, y + 20);
                    index++;
                }
                
                blink_counter = 0;
                cursor_visible = true;
            }
            
            // Cursor blinking
            blink_counter++;
            if(blink_counter >= 10) {
                blink_counter = 0;
                cursor_visible = !cursor_visible;
                setcolor(cursor_visible ? LIGHTGREEN : DARKGRAY);
                line(x + 5 + index*8, y + 20, x + 13 + index*8, y + 20);
            }
            
            delay(50);
        }
        
        input[index] = '\0';
        strcpy(str, input);
        return str;
    }

public:
    void drawInputWindow(const char* title, int x, int y, int w, int h) {
        left = x;
        top = y;
        right = x + w;
        bottom = y + h;
        
        // Window shadow
        setfillstyle(SOLID_FILL, BLACK);
        bar(x + 5, y + 5, right + 5, bottom + 5);
        
        // Main window background
        setfillstyle(SOLID_FILL, BLUE);
        bar(x, y, right, y + 30);  // Title bar
        
        setfillstyle(SOLID_FILL, DARKGRAY);  // Changed from LIGHTGRAY for better contrast
        bar(x, y + 30, right, bottom);  // Main content area
        
        // Window border
        setcolor(WHITE);
        rectangle(x, y, right, bottom);
        line(x, y + 30, right, y + 30);  // Title bar separator
        
        // Title text
        setcolor(LIGHTGREEN);  // Changed from YELLOW for better visibility
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(x + 10, y + 10, const_cast<char*>(title));
    }
    
    void drawButton(int x, int y, const char* text, int width = 150) {
        // Button shadow
        setfillstyle(SOLID_FILL, BLACK);
        bar(x + 2, y + 2, x + width + 2, y + 27);
        
        // Button body
        setfillstyle(SOLID_FILL, LIGHTBLUE);  // Changed from LIGHTGRAY
        bar(x, y, x + width, y + 25);
        
        // Button border
        setcolor(WHITE);  // Changed from BLACK
        rectangle(x, y, x + width, y + 25);
        
        // Button text
        setcolor(WHITE);  // Changed from BLACK
        int textX = x + (width - textwidth(const_cast<char*>(text))) / 2;
        int textY = y + (25 - textheight(const_cast<char*>(text))) / 2;
        outtextxy(textX, textY, const_cast<char*>(text));
    }
    
    char* getInput(int x, int y, const char* prompt, const char* units = "") {
        drawText(x, y + 7, prompt, LIGHTGREEN);  // Changed text color
        
        int inputX = x + textwidth(const_cast<char*>(prompt)) + 10;
        char* value = graphicsInput(inputX, y);
        
        if(strlen(units) > 0) {
            drawText(inputX + 120, y + 7, units, LIGHTGREEN);  // Changed text color
        }
        
        return value;
    }
};

// [Rest of the code remains the same - Shape class and main function]

class Shape {
private:
    int shapeType;      // 1: Triangle, 2: Rectangle, 3: Circle
    int x1, x2, x3;     // X coordinates
    int y1, y2, y3;     // Y coordinates
    int radius;         // For circle
    
public:
    Shape() {
        shapeType = 0;
        x1 = y1 = x2 = y2 = x3 = y3 = radius = 0;
    }
    
    void getInput() {
        GUI gui;
        cleardevice();
        
        // Shape selection window
        gui.drawInputWindow("Select Shape", 100, 50, 400, 300);
        gui.drawButton(150, 100, "1. Triangle");
        gui.drawButton(150, 140, "2. Rectangle");
        gui.drawButton(150, 180, "3. Circle");
        drawText(150, 230, "Enter choice (1-3): ");
        
        do {
            shapeType = atoi(gui.getInput(300, 230, ""));
        } while(shapeType < 1 || shapeType > 3);
        
        cleardevice();
        
        // Coordinate input window
        gui.drawInputWindow("Enter Coordinates", 100, 50, 400, 400);
        
        switch(shapeType) {
            case 1: // Triangle
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                drawText(150, 80, "Point");
                drawText(250, 80, "X");
                drawText(350, 80, "Y");
                
                setcolor(DARKGRAY);
                line(130, 100, 470, 100);
                
                drawText(150, 120, "Point 1:");
                x1 = atoi(gui.getInput(250, 120, "X1:"));
                y1 = atoi(gui.getInput(350, 120, "Y1:"));
                
                drawText(150, 170, "Point 2:");
                x2 = atoi(gui.getInput(250, 170, "X2:"));
                y2 = atoi(gui.getInput(350, 170, "Y2:"));
                
                drawText(150, 220, "Point 3:");
                x3 = atoi(gui.getInput(250, 220, "X3:"));
                y3 = atoi(gui.getInput(350, 220, "Y3:"));
                break;
                
            case 2: // Rectangle
                x1 = atoi(gui.getInput(150, 120, "Top-Left X:"));
                y1 = atoi(gui.getInput(150, 170, "Top-Left Y:"));
                x2 = atoi(gui.getInput(150, 220, "Width:"));
                y2 = atoi(gui.getInput(150, 270, "Height:"));
                break;
                
            case 3: // Circle
                x1 = atoi(gui.getInput(150, 120, "Center X:"));
                y1 = atoi(gui.getInput(150, 170, "Center Y:"));
                radius = atoi(gui.getInput(150, 220, "Radius:"));
                break;
        }
    }
    
    void draw(int color = WHITE) {
        setcolor(color);
        switch(shapeType) {
            case 1: // Triangle
                line(x1, y1, x2, y2);
                line(x2, y2, x3, y3);
                line(x3, y3, x1, y1);
                break;
                
            case 2: // Rectangle
                rectangle(x1, y1, x1 + x2, y1 + y2);
                break;
                
            case 3: // Circle
                circle(x1, y1, radius);
                break;
        }
    }
    
    void translate() {
        GUI gui;
        cleardevice();
        
        gui.drawInputWindow("Translation", 100, 50, 400, 200);
        int tx = atoi(gui.getInput(150, 100, "Translation X:"));
        int ty = atoi(gui.getInput(150, 140, "Translation Y:"));
        
        draw(WHITE); // Original shape
        
        switch(shapeType) {
            case 1: // Triangle
                x1 += tx; y1 += ty;
                x2 += tx; y2 += ty;
                x3 += tx; y3 += ty;
                break;
                
            case 2: // Rectangle
                x1 += tx; y1 += ty;
                break;
                
            case 3: // Circle
                x1 += tx; y1 += ty;
                break;
        }
        
        draw(GREEN); // Translated shape
    }
    
    void rotate() {
        if (shapeType == 3) {
            GUI gui;
            gui.drawInputWindow("Warning", 200, 200, 300, 100);
            drawText(220, 240, "Circle rotation not visible!");
            delay(2000);
            return;
        }
        
        GUI gui;
        cleardevice();
        
        gui.drawInputWindow("Rotation", 100, 50, 400, 200);
        float angle = atof(gui.getInput(150, 100, "Angle (degrees):"));
        
        angle = angle * M_PI / 180.0; // Convert to radians
        
        draw(WHITE); // Original shape
        
        // Calculate center point
        int cx, cy;
        if (shapeType == 1) {
            cx = (x1 + x2 + x3) / 3;
            cy = (y1 + y2 + y3) / 3;
        } else {
            cx = x1 + x2/2;
            cy = y1 + y2/2;
        }
        
        // Store original coordinates
        int ox1 = x1, oy1 = y1;
        int ox2 = x2, oy2 = y2;
        int ox3 = x3, oy3 = y3;
        
        // Rotate coordinates
        if (shapeType == 1) {
            x1 = cx + (ox1-cx)*cos(angle) - (oy1-cy)*sin(angle);
            y1 = cy + (ox1-cx)*sin(angle) + (oy1-cy)*cos(angle);
            x2 = cx + (ox2-cx)*cos(angle) - (oy2-cy)*sin(angle);
            y2 = cy + (ox2-cx)*sin(angle) + (oy2-cy)*cos(angle);
            x3 = cx + (ox3-cx)*cos(angle) - (oy3-cy)*sin(angle);
            y3 = cy + (ox3-cx)*sin(angle) + (oy3-cy)*cos(angle);
        } else if (shapeType == 2) {
            int temp = x2;
            x2 = abs(x2 * cos(angle));
            y2 = abs(temp * sin(angle));
        }
        
        draw(RED); // Rotated shape
    }
    
    void scale() {
        GUI gui;
        cleardevice();
        
        gui.drawInputWindow("Scaling", 100, 50, 400, 200);
        float sx = atof(gui.getInput(150, 100, "Scale X:"));
        float sy = atof(gui.getInput(150, 140, "Scale Y:"));
        
        draw(WHITE); // Original shape
        
        switch(shapeType) {
            case 1: { // Triangle
                int cx = (x1 + x2 + x3) / 3;
                int cy = (y1 + y2 + y3) / 3;
                
                x1 = cx + (x1 - cx) * sx;
                y1 = cy + (y1 - cy) * sy;
                x2 = cx + (x2 - cx) * sx;
                y2 = cy + (y2 - cy) * sy;
                x3 = cx + (x3 - cx) * sx;
                y3 = cy + (y3 - cy) * sy;
                break;
            }
            case 2: // Rectangle
                x2 *= sx;
                y2 *= sy;
                break;
                
            case 3: // Circle
                radius = radius * ((sx + sy) / 2);
                break;
        }
        
        draw(YELLOW); // Scaled shape
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    
    Shape shape;
    GUI gui;
    
    while(true) {
        cleardevice();
        
        // Main menu window
        gui.drawInputWindow("2D Transformation Menu", 100, 50, 400, 350);
        gui.drawButton(150, 100, "1. New Shape");
        gui.drawButton(150, 140, "2. Translate");
        gui.drawButton(150, 180, "3. Rotate");
        gui.drawButton(150, 220, "4. Scale");
        gui.drawButton(150, 260, "5. Exit");
        
        drawText(150, 300, "Enter choice: ");
        
        int choice;
        do {
            choice = atoi(gui.getInput(250, 300, ""));
        } while(choice < 1 || choice > 5);
        
        switch(choice) {
            case 1:
                shape.getInput();
                shape.draw();
                break;
            case 2:
                shape.translate();
                break;
            case 3:
                shape.rotate();
                break;
            case 4:
                shape.scale();
                break;
            case 5:
                closegraph();
                return 0;
        }
        
        outtextxy(70, 230, const_cast<char*>("Press any key to continue..."));
        getch();
    }
    
    return 0;
}