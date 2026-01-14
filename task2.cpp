#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <chrono>
#include <numeric>

using namespace std;

struct Result {
    int semester;
    string subject;
    int grade;
};

struct Student {
    string name;
    string group;
    vector<Result> results;
};

double computeAverage(
    const vector<Student>& students,
    const string& groupName,
    int semester,
    int start,
    int end
) {
    double total = 0;
    double count = 0;
    for (int i = start; i < end; ++i) {
        if (students[i].group == groupName) {
            for (auto& r : students[i].results) {
                total += r.grade;
                ++count;
            }
        }
    }
    if (count != 0.0) {
        return total / count;
    }
    else {
        return 0.0;
    }
}

int main()
{
    int n; // размер массива данных
    int threadsCount; // число потоков
    cout << "Введите кол-во студентов и кол-во потоков: ";
    cin >> n >> threadsCount;

    // массив студентов
    vector<Student> students(n);

    // ввод данных студентов
    for (int i = 0; i < n; ++i) {
        cout << "Студент " << i + 1 << "ФИО, группа, кол-во оценок: ";
        int numResults;
        cin >> students[i].name >> students[i].group >> numResults;
        for (int j = 0; j < numResults; ++j) {
            cout << "Семестр, предмет, оценка: ";
            cin >> students[i].results[j].semester >> students[i].results[j].subject >> students[i].results[j].grade;
        }
    }

    string targetGroup; // группа для анализа
    int targetSemester; // семестр
    cout << "Введите группу и семестр: ";
    cin >> targetGroup >> targetSemester;

    // без многопоточности
    auto start1 = chrono::high_resolution_clock::now(); // начало отсчета
    double avg1 = computeAverage(students, targetGroup, targetSemester, 0, n); // запустили функцию
    auto end1 = chrono::high_resolution_clock::now(); // конец отсчета
    chrono::duration<double> elapsed1 = end1 - start1; // вычислили время (из конца вычесть начало)
    cout << "Средняя оценка без потоков: " << avg1 << ", время: " << elapsed1.count() << " сек\n";

    // с многопоточностью
    auto start2 = chrono::high_resolution_clock::now();
    vector<thread> threads; // пустой вектор потоков
    vector<double> partialAverages(threadsCount, 0.0); // промежуточный результат для потока (одного)
    int chunk = n / threadsCount; // сколько студентов на один поток

    for (int t = 0; t < threadsCount; ++t) {
        int startIdx = t * chunk;
        int endIdx;

        if (t == threadsCount - 1) {
            endIdx = n; // если поток последний
        }
        else {
            endIdx = startIdx + chunk;
        }

        // запуск потоков
        threads.emplace_back([&students, &partialAverages, t, targetGroup, targetSemester, startIdx, endIdx]() 
            {
            partialAverages[t] = computeAverage(students, targetGroup, targetSemester, startIdx, endIdx);
            });
    }
    // завершение их работы
    for (auto& th : threads) {
        th.join();
    }

    // среднее время по всем потокам
    double avg2 = accumulate(partialAverages.begin(), partialAverages.end(), 0.0) / threadsCount;

    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed2 = end2 - start2;
    cout << "Средняя оценка с потоками: " << avg2 << ", время: " << elapsed2.count() << " сек\n";
}
