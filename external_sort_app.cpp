#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>
#include <filesystem>
#include <random>
#include <sstream>

using namespace std;

int delay = 50;

bool isFileExists(string filePath) {
    if (std::filesystem::exists(filePath)) {
        return 1;
    }
    return 0;
}

string getCurrentTime() {
    // Hàm được generate bởi Claude AI
    try {
        // Get current time_point from system_clock
        auto now = std::chrono::system_clock::now();

        // Convert to time_t (seconds since epoch)
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

        // Convert to local time structure
        std::tm local_tm{};
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&local_tm, &now_time_t); // Thread-safe on Windows
#else
        localtime_r(&now_time_t, &local_tm); // Thread-safe on POSIX
#endif

        // Print formatted time
        stringstream ss;
        ss << std::put_time(&local_tm, "%Y-%m-%d_%H-%M-%S");
        string result; ss >> result;
        return result;

    } catch (const std::exception &e) {
        std::cerr << "Error getting time: " << e.what() << std::endl;
        return "";
    }
}

void tao_file(vector<double>& numbers) {
    string fileName;
    cout << "Enter new file name: "; cin >> fileName;
    string currentTime = getCurrentTime();
    if (isFileExists(fileName + ".dat")) {
        cout << "There is already a file with the same name in this location. \nWant to rename to " << fileName
             << "_" << currentTime << ".dat? 1 (Yes) / 0 (No) : ";
        int check;
        if (!(cin >> check)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Illegal input (NaN). Canceled\n";
            return;
        }
        if (check == 1) fileName += "_" + currentTime;
        else {
            if (check != 0) cout << "Illegal input (Must be 0 or 1). Cancelled\n";
            return;
        }
    }
    fileName += ".dat";
    std::ofstream outFile(fileName, std::ios::binary);

    if (!outFile) {
        std::cerr << "Error creating file!" << std::endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    double min, max;
    cout << "Enter min number:    ";
    if (!(cin >> min)) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Illegal input (NaN). Canceled\n";
        return;
    }
    cout << "Enter max number:    "; 
    if (!(cin >> max)) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Illegal input (NaN). Canceled\n";
        return;
    }
    uniform_real_distribution<double> dis(min, max);

    int amount;
    cout << "Enter amount:        "; cin >> amount;
    for (int i = 0; i < amount; ++i) {
        double val = dis(gen);
        outFile.write(reinterpret_cast<const char*>(&val), sizeof(double));
    }
    
    outFile.close();

    std::ifstream file(fileName, ios::binary | ios::ate);

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    int count = size / sizeof(double);
    numbers = vector<double>(count, 0);

    file.read(reinterpret_cast<char*>(numbers.data()), size);
    file.close();

    std::cout << "Successfully created " << fileName << " with " << amount << " numbers." << std::endl;
    return;
}

void luu_file(vector<double> result) {
    string result_file_name;
    cout << "Enter the name: "; cin >> result_file_name;
    result_file_name += ".dat";
    if (isFileExists(result_file_name)) {
        cout << "There is already a file with the same name in this location. \nWant to replace? 1 (Yes) / 0 (No) : ";
        int check; cin >> check;
        if (check == 0) return;
    }
    ofstream outFile(result_file_name, std::ios::binary);
    if (outFile.is_open()) {
        for (auto &val : result)
        outFile.write(reinterpret_cast<const char*>(&val), sizeof(double));
        std::cout << "Succesfully saved in \"" << result_file_name <<"\"" << endl;
    } else {
        std::cout << "Can't open file." << endl;
    }
    outFile.close();
}

string tu_dong_liet_ke_file() {
    // Hàm được generate bởi Gemini AI
    std::vector<std::string> danh_sach_file;
    std::cout << "--- List of .dat and .bin files ---\n";
    
    int i = 1;
    for (const auto & entry : std::filesystem::directory_iterator(".")) {
        if (entry.path().extension() == ".dat" || entry.path().extension() == ".bin") {
            danh_sach_file.push_back(entry.path().string());
            std::cout << i++ << ". " << entry.path().filename().string() << "\n";
        }
    }

    if (danh_sach_file.empty()) {
        std::cout << "Not found any .dat or .bin files!\n";
        return "";
    }

    std::cout << "Choose file order: ";
    long long unsigned choice;
    std::cin >> choice;

    if (choice > 0 && choice <= danh_sach_file.size()) {
        return danh_sach_file[choice - 1];
    }
    return "";
}

void doc_file(vector<double>& numbers) {
    string file_name = tu_dong_liet_ke_file();
    if (file_name == "") return;
    ifstream file(file_name, ios::binary | ios::ate);    
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        cout << endl;
        system("pause");
        return;
    }

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    int count = size / sizeof(double);
    numbers = vector<double>(count, 0);

    if (file.read(reinterpret_cast<char*>(numbers.data()), size)) {
        cout << "Successfully read " << count << " numbers.\n";
    }
    cout << endl;
    file.close();
}

bool file_ton_tai(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void ve_bieu_do(const vector<double>& arr, const vector<int>& status) {
    // Hàm được generate bởi Gemini AI
    cout << "\033[H\033[?25l";

    double max_val = *max_element(arr.begin(), arr.end());
    if (max_val <= 0) max_val = 1;

    string buffer = "";
    for (size_t i = 0; i < arr.size(); i++) {
        buffer += (i < 10 ? " " : "") + to_string(i) + " | ";

        switch (status[i]) {
            case 1:  buffer += "\033[1;32m"; break; // Xanh lá: Đã xong
            case 2:  buffer += "\033[1;31m"; break; // Đỏ: Đang so sánh
            case 3:  buffer += "\033[1;33m"; break; // Vàng: Đặc biệt (Pivot/Min)
            default: buffer += "\033[1;34m"; break; // Xanh dương: Bình thường
        }

        int bar_length = (int)((arr[i] / max_val) * 40) + 1;
        for (int j = 0; j < bar_length; ++j) buffer += "#";
        
        for (int j = 0; j < 45 - bar_length; ++j) buffer += " ";

        buffer += "\033[0m " + to_string(arr[i]) + "    \n";
    }
    cout << buffer << flush;
    std::this_thread::sleep_for(chrono::milliseconds(delay));
}

vector<double> bubble_sort(vector<double> arr) {
    int n = arr.size();
    vector<int> status(n, 0);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            status[j] = status[j+1] = 2;
            ve_bieu_do(arr, status);

            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
            status[j] = status[j+1] = 0;
        }
        status[n - i - 1] = 1;
    }

    status[0] = 1;
    ve_bieu_do(arr, status);
    return arr;
}

vector<double> selection_sort(vector<double> arr) {
    int n = arr.size();
    vector<int> status(n, 0);

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < n; j++) {
            status[min_idx] = 3;
            status[j] = 2;
            ve_bieu_do(arr, status);
            
            if (arr[j] < arr[min_idx]) {
                status[min_idx] = 0;
                min_idx = j;
            } else {
                status[j] = 0;
            }
        }

        swap(arr[i], arr[min_idx]);
        status[min_idx] = 1;
        swap(status[i], status[min_idx]);
    }
    status[n-1] = 1;
    ve_bieu_do(arr, status);
    return arr;
}

vector<double> insertion_sort(vector<double> arr) {
    int n = arr.size();
    vector<int> status(n, 0);

    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;
        status[j + 1] = 2;

        while (j >= 0 && arr[j] > key) {
            status[j + 1] = 2;
            ve_bieu_do(arr, status);
            status[j + 1] = 1;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        status[j + 1] = 1;
        ve_bieu_do(arr, status);
    }
    return arr;
}

void merge(vector<double> &arr, int left, int mid, int right, vector<int> &status) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<double> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        status[left + i] = status[mid + 1 + j] = 2;
        ve_bieu_do(arr, status);

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        status[k] = 3; 
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        status[k] = 3;
        ve_bieu_do(arr, status);
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        status[k] = 3;
        ve_bieu_do(arr, status);
        j++;
        k++;
    }

    for (int p = left; p <= right; p++) status[p] = 1;
    ve_bieu_do(arr, status);
}

void merge_sort(vector<double> &arr, int left, int right, vector<int> &status) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid, status);
    merge_sort(arr, mid + 1, right, status);
    merge(arr, left, mid, right, status);
}

vector<double> merge_sort_visualization(vector<double> arr) {
    int n = arr.size();
    vector<int> status(n, 0);
    merge_sort(arr, 0, n - 1, status);
    return arr;
}

int partition(vector<double>& arr, int low, int high, vector<int> &status) {
    double pivot = arr[high];
    int i = low - 1;
    
    status[high] = 3;

    for (int j = low; j <= high - 1; j++) {
        status[j] = 2;
        ve_bieu_do(arr, status);
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
        status[j] = 0;
    }

    swap(arr[i + 1], arr[high]);  

    status[high] = 0;
    status[i + 1] = 1;
    ve_bieu_do(arr, status);
    return i + 1;
}

void quick_sort(vector<double> &arr, int low, int high, vector<int> &status) {
    if (low > high) return;
    if (low == high) {status[low] = 1; ve_bieu_do(arr, status);}

    int pi = partition(arr, low, high, status);
    quick_sort(arr, low, pi - 1, status);
    quick_sort(arr, pi + 1, high, status);
    for(int k = low; k <= high; k++) status[k] = 1;
}

vector<double> quick_sort_visualization(vector<double> arr) {
    int n = arr.size();
    vector<int> status(n, 0);
    quick_sort(arr, 0, n - 1, status);
    return arr;
}

void heapify(vector<double>& arr, int n, int i, vector<int>& status) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    status[i] = 2;
    if (l < n) status[l] = 2;
    if (r < n) status[r] = 2;
    ve_bieu_do(arr, status);

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        status[largest] = 3;
        ve_bieu_do(arr, status);
        
        swap(arr[i], arr[largest]);

        status[i] = status[largest] = 0;
        if (l < n) status[l] = 0;
        if (r < n) status[r] = 0;

        heapify(arr, n, largest, status);
    } else {
        status[i] = 0;
        if (l < n) status[l] = 0;
        if (r < n) status[r] = 0;
    }
}

void heap_sort(vector<double>& arr, vector<int>& status) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, status);
    }

    for (int i = n - 1; i > 0; i--) {
        status[0] = 3;
        status[i] = 2;
        ve_bieu_do(arr, status);

        swap(arr[0], arr[i]);
        
        status[i] = 1;
        status[0] = 0;

        heapify(arr, i, 0, status);
    }
    status[0] = 1;
    ve_bieu_do(arr, status);
}

vector<double> heap_sort_visualization(vector<double> arr) {
    int n = arr.size();
    vector<int> status(n, 0);
    heap_sort(arr, status);
    return arr;
}

bool da_sap_xep(const vector<double>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

vector<double> bogo_sort(vector<double> array) {
    std::random_device rd;
    std::default_random_engine engine(rd());

    vector<int> status(array.size(), 0);
    

    long long count = 0;

    while (!da_sap_xep(array) && count < 100000 ) {
        fill(status.begin(), status.end(), 2);
        
        std::shuffle(array.begin(), array.end(), engine);
        
        ve_bieu_do(array, status);
        
        count += delay;
        if (count >= 100000) cout << "Ughh... I can't sort this array, it is... too hard to be sorted?";
    }

    fill(status.begin(), status.end(), 1);
    ve_bieu_do(array, status);

    return array;
}



int main() {
    vector<double> numbers;
    vector<double> result;
    int choice;
    do {
        system("cls");
        cout << "--- SORTING APP ---" << endl;
        cout << "120. Choose Input file" << endl;
        cout << "130. Generate random Input file" << endl;
        cout << endl;
        cout << "1. Visualizing Bubble Sort" << endl;
        cout << "2. Visualizing Selection Sort" << endl;
        cout << "3. Visualizing Insertion Sort" << endl;
        cout << "4. Visualizing Merge Sort" << endl;
        cout << "5. Visualizing Quick Sort" << endl;
        cout << "6. Visualizing Heap Sort" << endl;
        cout << "7. Visualizing Bogo Sort" << endl;
        cout << endl;
        cout << "100. Change Visualizing Interval" << endl;
        cout << "110. Save the result" << endl;
        cout << "0. Exit" << endl;
        cout << endl;
        cout << "WARNING: The visualization can only work propertly if you don't scroll, and It is recommended to use it to represent fewer than 30 elements. (If more, it will not show propertly)." << endl;
        cout << endl;
        cout << "Choose an action: ";
        cin >> choice;

        system("cls");

        
        if (choice >= 1 && choice <= 11 && numbers.empty()) {
            cout << "The input is empty. Choose (120) or Generate (130) an Input file." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                result = bubble_sort(numbers);
                break;
            case 2:
                result = selection_sort(numbers);
                break;
            case 3:
                result = insertion_sort(numbers);
                break;
            case 4:
                result = merge_sort_visualization(numbers);
                break;
            case 5:
                result = quick_sort_visualization(numbers);
                break;
            case 6:
                result = heap_sort_visualization(numbers);
                break;
            case 7:
                if (numbers.size() > 7) {
                    cout << "Canh bao: Mang qua lon cho Bogo Sort! Ban co muon tiep tuc? (y/n): ";
                    char c; cin >> c;
                    if (c != 'y') break;
                }
                result = bogo_sort(numbers);
                break;
            case 100:
                cout << "Enter Interval (ms): "; cin >> delay;
                break;
            case 110:
                luu_file(result);
                break;
            case 120:
                doc_file(numbers);
                break;
            case 130:
                tao_file(numbers);
                break;
            
        }
        
        cout << endl;
        system("pause");
    } while (choice != 0);
    return 0;
}
