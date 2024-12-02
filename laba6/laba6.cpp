#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
//#include <windows.h>
#include <algorithm>

using namespace std;

class Course {
public:
    string courseName;
    int courseID;

    Course(string name, int id) : courseName(name), courseID(id) {}

    void display() const {
        cout << "Курс: " << courseName << " (ID: " << courseID << ")\n";
    }

    void editCourse() {
        string name;
        int id;

        cout << "Введите новое имя курса (оставьте пустым, чтобы не менять):";
        getline(cin, name);
        if (!name.empty()) courseName = name;

        cout << "Введите новый ID курса (введите -1, чтобы не менять):";
        cin >> id;
        if (id != -1) courseID = id;
    }
};

class Schedule {
private:
    unordered_map<string, vector<string>> weeklySchedule; // День недели и занятия

public:

    void getClass(const string& day, const string& className) {
        weeklySchedule[day].push_back(className);
    }
    void editClass() {
        string day;

        cout << "Введите день расписания:";
        getline(cin, day);
        if (!day.empty()) {
            auto it = weeklySchedule.find(day);
            if (it != weeklySchedule.end()) {
                int i = 0;
                for (auto item : it->second) {
                    string name;
                    cout << "1: " << it->second[i] << endl;
                    cout << "Введите замену (оставьте пустым, чтобы не менять):";
                    getline(cin, name);
                    if (!name.empty()) it->second[i] = name;
                    i++;
                }
            }
            else {
                cout << "Этого дня в расписании еще нет!" << endl;
            }
        }
    }

    void removeClassesByDay(const string& day) {
        auto it = weeklySchedule.find(day);
        if (it != weeklySchedule.end()) {
            weeklySchedule.erase(it);
            cout << "Все занятия в " << day << " удалены.\n";
        }
        else {
            cout << "Занятий в " << day << " не найдено.\n";
        }
    }

    void display() const {
        cout << "Расписание занятий:\n";
        for (const auto& day : weeklySchedule) {
            cout << day.first << ": ";
            for (const auto& className : day.second) {
                cout << className << ". ";
            }
            cout << "\n";
        }
    }
};

class Student {
private:
    string Name;
    string Surname;
    int studentID;

public:
    Student(string name, string surname, int id) : Name(name), Surname(surname), studentID(id) {}

    int getID() const {
        return studentID;
    }

    string getName() const {
        return Name + " " + Surname;
    }

    void setName(string newName) {
        Name = newName;
    }

    void setSurname(string newSurname) {
        Surname = newSurname;
    }

    void setID(int newID) {
        studentID = newID;
    }

    // РЕДАКТИРОВАНИЕ
    void editStudent() {
        string name, surname;
        int id;

        cout << "Введите новое имя студента (оставьте пустым, чтобы не менять):";
        getline(cin, name);
        if (!name.empty()) Name = name;

        cout << "Введите новую фамилию студента (оставьте пустым, чтобы не менять):";
        getline(cin, surname);
        if (!surname.empty()) Surname = surname;

        cout << "Введите новый ID студента (введите -1, чтобы не менять):";
        cin >> id;
        if (id != -1) studentID = id;
    }

    void display() const {
        cout << "Студент: " << getName() << " (ID: " << studentID << ")\n";
    }
};

class Professor {
private:
    string Name;
    string Surname;
    string Secondname;
    int professorID;
    vector<Course> coursesTaught;

public:
    Professor(string name, string surname, string secondname, int id) : Name(name), Surname(surname), Secondname(secondname), professorID(id) {}

    void addCourse(const Course& course) {
        coursesTaught.push_back(course);
    }

    void removeCoursesProfessor() const {
        cout << "Профессор: " << Name << " " << Surname << " " << Secondname
            << " (ID: " << professorID << ")\nПреподаваемые курсы:\n";
        for (const auto& course : coursesTaught) {
            course.display();
        }
    }

    int getID() const {
        return professorID;
    }

    string getName() const {
        return Name + " " + Surname;
    }

    void setName(string newName) {
        Name = newName;
    }

    void setSurname(string newSurname) {
        Surname = newSurname;
    }

    void setID(int newID) {
        professorID = newID;
    }

    void setSecondName(string newSecondName) {
        Secondname = newSecondName;
    }

    // РЕДАКТИРОВАНИЕ
    void editProfessor() {
        string name, surname, secondname;
        int id;

        cout << "Введите новое имя преподавателя (оставьте пустым, чтобы не менять):";
        getline(cin, name);
        if (!name.empty()) setName(name);

        cout << "Введите новую фамилию преподавателя (оставьте пустым, чтобы не менять):";
        getline(cin, surname);
        if (!surname.empty()) setSurname(surname);

        cout << "Введите новое отчество преподавателя (оставьте пустым, чтобы не менять):";
        getline(cin, secondname);
        if (!secondname.empty()) setSecondName(secondname);

        cout << "Введите новый ID преподавателя (введите -1, чтобы не менять):";
        cin >> id;
        if (id != -1) setID(id);
    }
};

class University {
private:
    vector<Student> students;       // Список студентов
    vector<Professor> professors;   // Список преподавателей
    vector<Course> courses;         // Список курсов
    Schedule schedule;              // Расписание

public:

    //ГЕТТЕРЫ
    void getStudent(const Student& student) {
        students.push_back(student);
    }

    void getProfessor(const Professor& professor) {
        professors.push_back(professor);
    }

    void getCourse(const Course& course) {
        courses.push_back(course);
    }

    void getSchedule(const string& day, const string& className) {
        schedule.getClass(day, className);
    }

    //СЕТТЕРЫ
    void setStudent(int id, const Student& student) { students[id] = student; }

    void setProfessor(size_t id, const Professor& professor) { professors[id] = professor; }

    void setCourse(size_t id, const Course& course) { courses[id] = course; }

    void setSchedule(const string& day, const string& className) { schedule.editClass(); }

    //УДАЛЕНИЕ
    void removeStudent(int studentID) {
        auto it = find_if(students.begin(), students.end(), [&](const Student& s) {
            return s.getID() == studentID;
            });

        if (it != students.end()) {
            students.erase(it);
            cout << "Студент с ID " << studentID << " успешно удален.\n";
        }
        else {
            cout << "Студент с ID " << studentID << " не найден.\n";
        }
    }

    void removeProfessor(int professorID) {
        auto it = find_if(professors.begin(), professors.end(), [&](const Professor& professor) {
            return professor.getID() == professorID;
            });

        if (it != professors.end()) {
            professors.erase(it);
            cout << "Профессор с ID " << professorID << " успешно удален.\n";
        }
        else {
            cout << "Профессор с ID " << professorID << " не найден.\n";
        }
    }

    void removeCourse(int courseID) {
        auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
            return c.courseID == courseID;
            });

        if (it != courses.end()) {
            courses.erase(it);
            cout << "Курс с ID " << courseID << " успешно удален.\n";
        }
        else {
            cout << "Курс с ID " << courseID << " не найден.\n";
        }
    }

    void removeSchedule(const string& day) {
        schedule.removeClassesByDay(day);
    }
    //РЕДАКТИРОВАНИЕ
    void editStudent(Student& student) {
        auto it = std::find_if(students.begin(), students.end(), [&](const Student& man) {
            return man.getID() == student.getID();
            });

        if (it != students.end()) {
            it->editStudent(); // редактируем найденного студента
            it->display(); // показываем информацию о студенте
            //removeStudent(student.getID()); 
            cout << "Студент успешно редактирован.\n";
            cout << "Теперь перейдите в удаление и введите новый id(т.к создалась копия) .\n";
            getStudent(*it); // добавляем обновлённую запись
        }
        else {
            cerr << "Студент с id " << student.getID() << " не найден!" << endl;
        }
    }

    void editProfessor(Professor& professor) {
        auto it = find_if(professors.begin(), professors.end(), [&](const Professor& man) {
            return man.getID() == professor.getID();
            });

        if (it != professors.end()) {
            it->editProfessor(); // Аналогично с студентом
            //removeProfessor(professor.getID()); 
            cout << "Профессор успешно редактирован.\n";
            cout << "Теперь перейдите в удаление и введите новый id(т.к создалась копия) .\n";
            getProfessor(*it); 
        }
        else {
            cerr << "Профессор с id " << professor.getID() << " не найден!" << endl;
        }
    }

    void editCourse(Course& course) {
        auto it = find_if(courses.begin(), courses.end(), [&](const Course& subject) {
            return subject.courseID == course.courseID;
            });

        if (it != courses.end()) {
            it->editCourse(); // Аналогично с студентом
            //removeCourse(course.courseID); 
            cout << "Курс успешно редактирован.\n";
            cout << "Теперь перейдите в удаление и введите новый id(т.к создалась копия) .\n";
            getCourse(*it); 
        }
        else {
            cerr << "Курс с id " << course.courseID << " не найден!" << endl;
        }
    }

    void editSchedule() {
        schedule.editClass(); 
    }

    //ПОИСК 
    Student findStudentByID(int ID) const {
        auto it = find_if(students.begin(), students.end(), [ID](const Student& student) {
            return student.getID() == ID;
            });

        if (it != students.end()) {
            return *it;
        }
        else {
            cout << "Студент с таким ID не найден" << endl;
        }
    }


    Professor findProfessorByID(int ID) const {
        auto it = find_if(professors.begin(), professors.end(), [ID](const Professor& professor) {
            return professor.getID() == ID;
            });

        if (it != professors.end()) {
            return *it;
        }
        else {
            cout << "Профессор с таким ID не найден" << endl;
        }
    }

    Course findCourseByID(int ID) const {
        auto it = find_if(courses.begin(), courses.end(), [ID](const Course& course) {
            return course.courseID == ID;
            });

        if (it != courses.end()) {
            return *it;
        }
        else {
            cout << "Курс с таким ID не найден" << endl;
        }
    }


    //ВЫВОД
    void displayAllStudents() const {
        cout << "Список студентов:\n";
        for (const auto& student : students) {
            student.display();
        }
    }

    void displayAllProfessors() const {
        cout << "Список преподавателей:\n";
        for (const auto& professor : professors) {
            cout << "ID: " << professor.getID() << " | ФИО: " << professor.getName() << endl;
        }
    }

    void displayAllCourses() const {
        cout << "Список курсов:\n";
        for (const auto& course : courses) {
            course.display();
        }
    }

    void displaySchedule() const {
        schedule.display();
    }
};

int main() {
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Rus");

    University university;
    int choice;

    do {
        cout << "\nМАУ_admin\n";
        cout << "Главное меню:\n";
        cout << "1. Управление студентами\n";
        cout << "2. Управление преподавателями\n";
        cout << "3. Управление курсами\n";
        cout << "4. Управление расписанием\n";
        cout << "5. СПРАВКА!!!\n";
        cout << "6. Выйти\n";
        cout << "Выберите пункт меню: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int studentChoice;
            do {
                cout << "\nУправление студентами:\n";
                cout << "1. Добавить студента\n";
                cout << "2. Редактировать студента\n";
                cout << "3. Удалить студента\n";
                cout << "4. Показать всех студентов\n";
                cout << "5. Вернуться в главное меню\n";
                cout << "Введите номер действия:";
                cin >> studentChoice;
                cin.ignore();

                switch (studentChoice) {
                case 1: {
                    string name, surname;
                    int id;
                    cout << "Введите имя студента:";
                    getline(cin, name);
                    cout << "Введите фамилию студента:";
                    getline(cin, surname);
                    cout << "Введите ID студента:";
                    cin >> id;
                    university.getStudent(Student(name, surname, id));
                    break;
                }
                case 2: {
                    int id;
                    cout << "Введите ID студента для редактирования:";
                    cin >> id;
                    cin.ignore();

                    Student student = university.findStudentByID(id);
                    if (student.getID() != -1) { 
                        university.editStudent(student);
                    }
                    else {
                        cout << "Студент с таким ID не найден.\n";
                    }
                    break;
                }
                case 3: {
                    int id;
                    cout << "Введите ID студента для удаления: ";
                    cin >> id;
                    university.removeStudent(id);
                    break;
                }
                case 4: {
                    university.displayAllStudents();
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            } while (studentChoice != 5);
            break;
        }
        case 2: {
            int professorChoice;
            do {
                cout << "\nУправление преподавателями:\n";
                cout << "1. Добавить преподавателя\n";
                cout << "2. Редактировать преподавателя\n";
                cout << "3. Удалить преподавателя\n";
                cout << "4. Показать всех преподавателей\n";
                cout << "5. Вернуться в главное меню\n";
                cout << "Введите номер действия: ";
                cin >> professorChoice;
                cin.ignore();

                switch (professorChoice) {
                case 1: {
                    string name, surname, secondname;
                    int id;
                    cout << "Введите имя преподавателя: ";
                    getline(cin, name);
                    cout << "Введите фамилию преподавателя: ";
                    getline(cin, surname);
                    cout << "Введите отчество преподавателя: ";
                    getline(cin, secondname);
                    cout << "Введите ID преподавателя: ";
                    cin >> id;
                    university.getProfessor(Professor(name, surname, secondname, id));
                    break;
                }
                case 2: {
                    int id;
                    cout << "Введите ID преподавателя для редактирования: ";
                    cin >> id;
                    cin.ignore();

                    Professor professor = university.findProfessorByID(id); // Поиск профессора по ID
                    if (professor.getID() != -1) { // Проверка на существование профессора (так ничего не проверится)
                        university.editProfessor(professor);
                    }
                    else {
                        cout << "Преподаватель с таким ID не найден.\n";
                    }
                    break;
                }

                case 3: {
                    int id;
                    cout << "Введите ID преподавателя для удаления: ";
                    cin >> id;
                    university.removeProfessor(id);
                    break;
                }
                case 4: {
                    university.displayAllProfessors();
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            } while (professorChoice != 5);
            break;
        }
        case 3: {
            int courseChoice;
            do {
                cout << "\nУправление курсами:\n";
                cout << "1. Добавить курс\n";
                cout << "2. Редактировать курс\n";
                cout << "3. Удалить курс\n";
                cout << "4. Показать все курсы\n";
                cout << "5. Вернуться в главное меню\n";
                cout << "Введите номер действия: ";
                cin >> courseChoice;
                cin.ignore();

                switch (courseChoice) {
                case 1: {
                    string name;
                    int id;
                    cout << "Введите название курса: ";
                    getline(cin, name);
                    cout << "Введите ID курса: ";
                    cin >> id;
                    university.getCourse(Course(name, id));
                    break;
                }
                case 2: {
                    int id;
                    cout << "Введите ID курса для редактирования:";
                    cin >> id;
                    cin.ignore();

                    Course course = university.findCourseByID(id);
                    if (course.courseID != -1) {
                        university.editCourse(course);
                    }
                    else {
                        cout << "Курс с таким ID не найден.\n";
                    }
                    break;
                }
                case 3: {
                    int id;
                    cout << "Введите ID курса для удаления: ";
                    cin >> id;
                    university.removeCourse(id);
                    break;
                }
                case 4: {
                    university.displayAllCourses();
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            } while (courseChoice != 5);
            break;
        }
        case 4: {
            int scheduleChoice;
            do {
                cout << "\nУправление расписанием:\n";
                cout << "1. Добавить расписание\n";
                cout << "2. Изменить расписание\n";
                cout << "3. Удалить расписание\n";
                cout << "4. Показать расписание\n";
                cout << "5. Вернуться в главное меню\n";
                cout << "Введите номер действия: ";
                cin >> scheduleChoice;
                cin.ignore();

                switch (scheduleChoice) {
                case 1: {
                    string day, className;
                    cout << "Введите день недели: ";
                    getline(cin, day);
                    cout << "Введите название занятия: ";
                    getline(cin, className);
                    university.getSchedule(day, className);
                    break;
                }
                case 2: {
                    university.editSchedule();
                    break;
                }
                case 3: {
                    string day;
                    cout << "Введите день недели для удаления: ";
                    cin >> day;
                    university.removeSchedule(day);
                    break;
                }
                case 4: {
                    university.displaySchedule();
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            } while (scheduleChoice != 5);
            break;
        }
        case 5:
            cout << "Данная программа поможет вам работать со студентами,преподавателями,курсами и даже расписанием!\n";
            cout << "Самое главное пишите все на ENGLISH!(Даже если вы тестер)\n";
            break;
        case 6:
            cout << "Хорошего Дня!!!\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 6);
    return 0;
}
