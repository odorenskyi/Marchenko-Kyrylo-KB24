#ifndef STRUCT_TYPE_PROJECT_N_H
#define STRUCT_TYPE_PROJECT_N_H

#include <string>
#include <iostream>
#include <fstream>

// Структура для зберігання інформації про поштове відділення
struct PostalRecord {
    int index;                  // П'ятизначний індекс
    std::string region;         // Область
    std::string district;       // Район
    std::string city;           // Населений пункт
    std::string postal_office;  // ВПЗ, що обслуговує

    // Конструктор за замовчуванням
    PostalRecord() : index(0) {}

    // Конструктор з параметрами
    PostalRecord(int idx, const std::string& reg, const std::string& dist,
                 const std::string& c, const std::string& office)
    : index(idx), region(reg), district(dist), city(c), postal_office(office) {}

    // Оператор виведення для зручного відображення
    friend std::ostream& operator<<(std::ostream& os, const PostalRecord& record) {
        os << "Індекс: " << record.index
        << ", Область: " << record.region
        << ", Район: " << record.district
        << ", Місто: " << record.city
        << ", ВПЗ: " << record.postal_office;
        return os;
    }

    // Оператор порівняння для пошуку
    bool operator==(const PostalRecord& other) const {
        return index == other.index;
    }
};

// Вузол двозв'язного списку
struct ListNode {
    PostalRecord data;     // Дані запису
    ListNode* next;        // Вказівник на наступний елемент
    ListNode* prev;        // Вказівник на попередній елемент

    // Конструктор за замовчуванням
    ListNode() : next(nullptr), prev(nullptr) {}

    // Конструктор з даними
    ListNode(const PostalRecord& record)
    : data(record), next(nullptr), prev(nullptr) {}

    // Деструктор
    ~ListNode() {
        // Автоматичне очищення пам'яті для рядків
    }
};

// Клас для управління двозв'язним списком поштових записів
class PostalDatabase {
private:
    ListNode* head;        // Вказівник на початок списку
    ListNode* tail;        // Вказівник на кінець списку
    int size;              // Кількість елементів у списку

    // Приватний метод для очищення всього списку
    void clearList();

public:
    PostalDatabase();

    ~PostalDatabase();

    // Заборона копіювання (для безпеки пам'яті)
    PostalDatabase(const PostalDatabase&) = delete;
    PostalDatabase& operator=(const PostalDatabase&) = delete;

    // Основні операції над списком

    // Функції, які реалізовуватиме Іванов:
    bool loadFromFile(const std::string& filename);        // Завантаження з бінарного файлу
    bool saveToFile(const std::string& filename);          // Збереження у бінарний файл
    void exportToFile(const std::string& filename) const;  // Експорт у текстовий файл

    // Функції, які реалізовуватиме Марченко:
    ListNode* searchByIndex(int index);                    // Пошук за індексом
    ListNode* searchByCity(const std::string& city);       // Пошук за містом
    void displayAll() const;                               // Виведення всіх записів на екран

    // Функції, які реалізовуватиме Куртяк:
    void addRecord(const PostalRecord& record);            // Додавання запису
    bool deleteRecord(int index);                          // Видалення запису за індексом

    // Допоміжні функції (спільні)
    int getSize() const;                                   // Отримання розміру списку
    bool isEmpty() const;                                  // Перевірка чи список порожній
    void clear();                                          // Очищення всього списку

    // Функції для роботи з ітераторами (для зручності)
    ListNode* getFirst() const { return head; }
    ListNode* getLast() const { return tail; }

    // Функція для валідації індексу
    static bool isValidIndex(int index) {
        return index >= 10000 && index <= 99999;
    }

    // Функція для отримання статистики
    void printStatistics() const;
};


// Допоміжні функції для роботи з файлами та валідації
namespace PostalUtils {
    // Функція для валідації даних запису
    bool validateRecord(const PostalRecord& record);

    // Функція для форматування виведення
    std::string formatRecord(const PostalRecord& record);

    // Функція для парсингу рядка в запис
    PostalRecord parseRecord(const std::string& line);

    // Функція для створення резервної копії
    bool createBackup(const std::string& filename);
}

// Константи для роботи програми
namespace PostalConstants {
    const std::string DEFAULT_FILENAME = "postal_database.dat";
    const std::string BACKUP_EXTENSION = ".backup";
    const std::string EXPORT_EXTENSION = ".txt";
    const int MAX_RECORDS = 100000;  // Максимальна кількість записів
    const int MIN_INDEX = 10000;     // Мінімальний індекс
    const int MAX_INDEX = 99999;     // Максимальний індекс
}

#endif // STRUCT_TYPE_PROJECT_N_H
