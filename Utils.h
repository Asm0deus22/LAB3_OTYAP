///////////////////
// FILE: Utils.h //
///////////////////
namespace ATOSUtils { // ВЫ МЕНЯ СПРОСИТЕ - ЗАЧЕМ? ATOI УЯЗВИМА ПРИ ОГРОМНЫХ ТЕСТАХ. Боюсь, это правда...
    struct ATOSResult { // структура-отчет по исполнении функции ATOS
        bool overflowFlag; // флаг переполнения(здесь нету такого, а ATOI также уязвим против переполнения)
        bool invalidFlag; // флаг ошибки(схавал наверное не то)
        short value; // собственно значение. При отсутствии флагов оно равно значению из текста
        ATOSResult() : value(0), overflowFlag(false), invalidFlag(false) {}
    };
    ATOSResult ATOS(char *p) { // функция перевода строки в short
        ATOSResult result = ATOSResult(); // формируем отчет
        int buffer = 0; // переменная буфер, которая будет в себе хранить собственно говоря значение
        bool minus = (*p == '-'); // флаг минуса
        if (minus) p++;
        while (*p && !result.overflowFlag && !result.invalidFlag) { // пока что-то да валидно, выполняем действие(до конца строки)
            if (*p < '0' || *p > '9') result.invalidFlag = !result.invalidFlag; // встретили не-цифру десятичную, флаг ошибки устанавливаем
            else {
                buffer *= 10; // сдвигаем число
                buffer += (*p - '0'); // добавляем цифру
                if (minus) { // особая проверка на переполнение
                    if (buffer > 0 && ((buffer-1) & 0xFFFF8000)) result.overflowFlag = !result.overflowFlag; // если обнаружили, что заехало -> устанавливаем флаг переполнения
                } else {
                    if (buffer & 0xFFFF8000) result.overflowFlag = !result.overflowFlag;
                }
                p++; // сдвигаем указатель
            }
        }
        if (!result.overflowFlag && !result.invalidFlag) { // проверяем на ошибки
            if (minus) buffer = -buffer;
            result.value = buffer;
        }
        return result; // возвращаем результат
    }
}
//////////////////////////
// END OF FILE: Utils.h //
//////////////////////////