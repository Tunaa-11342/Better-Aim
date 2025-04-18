#pragma once

KEYBOARD_KEYS getKeyFromString(const std::string& keyName) {
    static const std::unordered_map<std::string, KEYBOARD_KEYS> keyMap = {
        {"left_mouse_button", left_mouse_button},
        {"right_mouse_button", right_mouse_button},
        {"x1", x1},
        {"x2", x2},
        {"num_0", num_0},
        {"num_1", num_1},
        {"num_2", num_2},
        {"num_3", num_3},
        {"num_4", num_4},
        {"num_5", num_5},
        {"num_6", num_6},
        {"num_7", num_7},
        {"num_8", num_8},
        {"num_9", num_9},
        {"a", a},
        {"b", b},
        {"c", c},
        {"d", d},
        {"e", e},
        {"f", f},
        {"g", g},
        {"h", h},
        {"i", i},
        {"j", j},
        {"k", k},
        {"l", l},
        {"m", m},
        {"n", n},
        {"o", o},
        {"p", p},
        {"q", q},
        {"r", r},
        {"s", s},
        {"t", t},
        {"u", u},
        {"v", v},
        {"w", w},
        {"x", x},
        {"y", y},
        {"z", z},
        {"backspace", backspace},
        {"down_arrow", down_arrow},
        {"enter", enter},
        {"esc", esc},
        {"home", home},
        {"insert", insert},
        {"left_alt", left_alt},
        {"left_ctrl", left_ctrl},
        {"left_shift", left_shift},
        {"page_down", page_down},
        {"page_up", page_up},
        {"right_alt", right_alt},
        {"right_ctrl", right_ctrl},
        {"right_shift", right_shift},
        {"space", space},
        {"tab", tab},
        {"up_arrow", up_arrow},
        {"f1", f1},
        {"f2", f2},
        {"f3", f3},
        {"f4", f4},
        {"f5", f5},
        {"f6", f6},
        {"f7", f7},
        {"f8", f8},
        {"f9", f9},
        {"f10", f10},
        {"f11", f11},
        {"f12", f12}
    };

    auto it = keyMap.find(keyName);
    if (it != keyMap.end()) {
        return it->second;
    }
    else {
        throw std::invalid_argument("Invalid key name: " + keyName);
    }
}

bool isValidKey(std::string key) {
    if (key == "left_mouse_button") return true;
    else if (key == "right_mouse_button ") return true;
    else if (key == "x1") return true;
    else if (key == "x2") return true;
    else if (key == "num_0") return true;
    else if (key == "num_1") return true;
    else if (key == "num_2") return true;
    else if (key == "num_3") return true;
    else if (key == "num_4") return true;
    else if (key == "num_5") return true;
    else if (key == "num_6") return true;
    else if (key == "num_7") return true;
    else if (key == "num_8") return true;
    else if (key == "num_9") return true;
    else if (key == "a") return true;
    else if (key == "b") return true;
    else if (key == "c") return true;
    else if (key == "d") return true;
    else if (key == "e") return true;
    else if (key == "f") return true;
    else if (key == "g") return true;
    else if (key == "h") return true;
    else if (key == "i") return true;
    else if (key == "j") return true;
    else if (key == "k") return true;
    else if (key == "l") return true;
    else if (key == "m") return true;
    else if (key == "n") return true;
    else if (key == "o") return true;
    else if (key == "p") return true;
    else if (key == "q") return true;
    else if (key == "r") return true;
    else if (key == "s") return true;
    else if (key == "t") return true;
    else if (key == "u") return true;
    else if (key == "v") return true;
    else if (key == "w") return true;
    else if (key == "x") return true;
    else if (key == "y") return true;
    else if (key == "z") return true;
    else if (key == "backspace") return true;
    else if (key == "down_arrow") return true;
    else if (key == "enter") return true;
    else if (key == "esc") return true;
    else if (key == "home") return true;
    else if (key == "insert") return true;
    else if (key == "left_alt") return true;
    else if (key == "left_ctrl") return true;
    else if (key == "left_shift") return true;
    else if (key == "page_down") return true;
    else if (key == "page_up") return true;
    else if (key == "right_alt") return true;
    else if (key == "right_ctrl") return true;
    else if (key == "right_shift") return true;
    else if (key == "space") return true;
    else if (key == "tab") return true;
    else if (key == "up_arrow") return true;
    else if (key == "f1") return true;
    else if (key == "f2") return true;
    else if (key == "f3") return true;
    else if (key == "f4") return true;
    else if (key == "f5") return true;
    else if (key == "f6") return true;
    else if (key == "f7") return true;
    else if (key == "f8") return true;
    else if (key == "f9") return true;
    else if (key == "f10") return true;
    else if (key == "f11") return true;
    else if (key == "f12") return true;
    else return false;
}