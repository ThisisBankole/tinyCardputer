#include "M5Cardputer.h"
#include "splash.h"
#include <vector>

bool editor_mode = false;
std::vector<String> editor_lines = { "" };
int editor_line = 0;
int editor_col = 0;

M5Canvas canvas(&M5Cardputer.Display);
String input = "> ";
String current_cmd = "";



void beepTone(int freq, int ms = 620) {
    M5Cardputer.Speaker.tone(freq, ms);
}

void wait(float seconds) { delay(seconds * 1000); }

void bootSound() {
    beepTone(1600); wait(0.2);
    beepTone(1900); wait(0.2);
    beepTone(1200); 
}

void terminal_print(const String &msg) {
    canvas.println(msg);
    canvas.pushSprite(4, 4);
}

void ascii_window(const String &msg) {
    terminal_print("+----------------------------+");
    terminal_print("|          WINDOW            |");
    terminal_print("+----------------------------+");
    terminal_print("| " + msg);
    terminal_print("+----------------------------+");
}




void process_command(String cmd) {
    cmd.trim();
    terminal_print("> " + cmd);

    String lower = cmd; lower.toLowerCase();

    if (lower == "minicoder") {
        editor_mode = true;
        editor_lines = { "" };
        editor_line = 0;
        editor_col = 0;
        canvas.fillSprite(BLACK);
        M5Cardputer.Display.fillScreen(BLACK);
        return;
    }

    if (lower == "help") {
        ascii_window(
            "help - Show this message\n"
            "echo [txt] - Print text on terminal\n"
            "beep [hz] - sounds a beeper\n"
            "window [msg] - show ASCII screen\n"
            "boot - call boot sound\n"
            "error - call error sound\n"
            "clear - Clear terminal\n"
            "minicoder - enter code editor\n"
            "exit"
        );
        return;
    }

    if (lower == "clear") {
        canvas.fillSprite(BLACK);
        canvas.pushSprite(4, 4);
        return;
    }

    if (lower.startsWith("echo ")) {
        terminal_print(cmd.substring(5));
        return;
    }

    if (lower.startsWith("beep ")) {
        int hz = cmd.substring(5).toInt();
        beepTone(hz);
        return;
    }

    if (lower.startsWith("window ")) {
        ascii_window(cmd.substring(7));
        return;
    }

    if (lower == "error") {
        beepTone(900); wait(0.1); beepTone(400);
        return;
    }

    if (lower == "boot") {
        bootSound();
        return;
    }

    terminal_print("Unknown command.");
}


void draw_editor() {
    canvas.fillSprite(BLACK);

    canvas.println("=== miniCoder v1.0 ===");
    canvas.println("CTRL+ENTER = Run | TAB = Exit");
    canvas.println("--------------------------------");

    for (int i = 0; i < editor_lines.size(); i++) {
        String ln = String(i + 1) + " | ";
        canvas.print(ln);
        canvas.println(editor_lines[i]);
    }

    canvas.pushSprite(4, 4);
}

void editor_backspace() {
    if (editor_col > 0) {
        String &line = editor_lines[editor_line];
        line = line.substring(0, editor_col - 1) + line.substring(editor_col);
        editor_col--;
    }
    else if (editor_line > 0) {
        editor_col = editor_lines[editor_line - 1].length();
        editor_lines[editor_line - 1] += editor_lines[editor_line];
        editor_lines.erase(editor_lines.begin() + editor_line);
        editor_line--;
    }
}

void editor_add_char(char c) {
    String &line = editor_lines[editor_line];
    line = line.substring(0, editor_col) + c + line.substring(editor_col);
    editor_col++;
}

void editor_newline() {
    String &line = editor_lines[editor_line];
    String tail = line.substring(editor_col);
    line = line.substring(0, editor_col);
    editor_lines.insert(editor_lines.begin() + editor_line + 1, tail);
    editor_line++;
    editor_col = 0;
}

void redraw_terminal_ui() {
    M5Cardputer.Display.fillScreen(BLACK);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(GREEN);


    M5Cardputer.Display.drawRect(
        0, 0,
        M5Cardputer.Display.width(),
        M5Cardputer.Display.height() - 28,
        GREEN
    );

    M5Cardputer.Display.fillRect(
        0, M5Cardputer.Display.height() - 4,
        M5Cardputer.Display.width(),
        4,
        GREEN
    );


    canvas.fillSprite(BLACK);
    canvas.pushSprite(4, 4);


    M5Cardputer.Display.drawString(input, 4, M5Cardputer.Display.height() - 24);
}

void run_script() {
    terminal_print("Running script...");

    for (auto &line : editor_lines) {
        String cmd = line;
        cmd.trim();

        if (cmd.length() == 0) continue;
        if (cmd == "//") continue;

        String lower = cmd;
        lower.toLowerCase();

        if (lower.startsWith("beep ")) {
            float hz = cmd.substring(5).toFloat();
            beepTone(hz);
            wait(0.1);
            continue;
        }

        if (lower.startsWith("window ")) {
            ascii_window(cmd.substring(7));
            wait(0.1);
            continue;
        }

        if (lower.startsWith("echo ")) {
            terminal_print(cmd.substring(5));
            wait(1.0);
            continue;
        }

        if (lower.startsWith("wait ")) {
            float sec = cmd.substring(5).toFloat();
            wait(sec);
            continue;
        }

        if (lower == "boot") {
            bootSound();
            wait(0.2);
            continue;
        }

        if (lower == "error") {
            beepTone(900);
            wait(0.1);
            beepTone(300);
            wait(0.2);
            continue;
        }

        if (lower == "help") {
            ascii_window(
                "echo -> show message\n"
                "beep -> uses beeper\n"
                "wait -> wait any time\n"
                "boot -> play boot sound\n"
                "window -> create window\n"
                "help -> show this help"
            );
            continue;
        }

        terminal_print("Unknown: " + cmd);
    }

    terminal_print("Script complete.");
    draw_editor();
}

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);

    M5Cardputer.Display.fillScreen(BLACK);
    M5Cardputer.Display.drawJpg(splash_jpg, splash_jpg_len, 0, 0);
    bootSound();
    delay(2000);


    M5Cardputer.Display.fillScreen(BLACK);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(GREEN);

    M5Cardputer.Display.drawRect(0, 0,
        M5Cardputer.Display.width(),
        M5Cardputer.Display.height() - 28,
        GREEN);

    M5Cardputer.Display.fillRect(0,
        M5Cardputer.Display.height() - 4,
        M5Cardputer.Display.width(),
        4, GREEN);

    canvas.setTextSize(1);
    canvas.setTextFont(&fonts::Font0);
    canvas.setTextScroll(true);
    canvas.createSprite(
        M5Cardputer.Display.width() - 8,
        M5Cardputer.Display.height() - 36);

    terminal_print("tinyCardputer TERMINAL v1.0");
    terminal_print("Type 'help'");
}


void loop() {
    M5Cardputer.update();

    if (!M5Cardputer.Keyboard.isChange()) return;

    auto status = M5Cardputer.Keyboard.keysState();


    if (editor_mode) {


        if (status.ctrl && status.enter) {
            run_script();
            return;
        }


        if (status.tab) {
            editor_mode = false;
            redraw_terminal_ui();     
            terminal_print("--- Exiting miniCoder ---");   
            terminal_print("Exited miniCoder (use 'minicoder' to return).");
            terminal_print("type 'help' for commands.");
            return;
        }


        if (status.enter && !status.ctrl) {
            editor_newline();
        }


        if (status.del) {
            editor_backspace();
        }


        for (char c : status.word) {
            editor_add_char(c);
        }

        draw_editor();
        return;
    }



    for (auto c : status.word) {
        input += c;
        current_cmd += c;
    }

    if (status.del) {
        if (input.length() > 2) input.remove(input.length() - 1);
        if (current_cmd.length() > 0) current_cmd.remove(current_cmd.length() - 1);
    }

    if (status.enter) {
        process_command(current_cmd);
        input = "> ";
        current_cmd = "";
    }

    M5Cardputer.Display.fillRect(
        0, M5Cardputer.Display.height() - 28,
        M5Cardputer.Display.width(), 25, BLACK);

    M5Cardputer.Display.drawString(input, 4, M5Cardputer.Display.height() - 24);
}
