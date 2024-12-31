#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100 //Tao mang toi da la 100 nguoi
#define FILENAME "users.txt" // ten file luu gia tri nguoi dung

typedef struct {
    char id[20];
    char name[50];
    char email[50];
    char phone[15];
    int gender; // 0: Male, 1: Female
    int day, month, year;
    char username[50];
    long long balance;
    int status; // 0: Locked, 1: Active
} User;

User users[MAX_USERS];
int userCount = 0;

//Doc du lieu nguoi dung tu file
void readUsersFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    while (fscanf(file, "%s %s %s %s %d %d %d %d %s %lld %d\n",
                  users[userCount].id, users[userCount].name, users[userCount].email, users[userCount].phone,
                  &users[userCount].gender, &users[userCount].day, &users[userCount].month, &users[userCount].year,
                  users[userCount].username, &users[userCount].balance, &users[userCount].status) != EOF) {
        userCount++;
        if (userCount >= MAX_USERS) break;
    }
    fclose(file);
}

// Luu du lieu vao file
void saveUsersToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving user data.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %s %s %d %d %d %d %s %lld %d\n",
                users[i].id, users[i].name, users[i].email, users[i].phone,
                users[i].gender, users[i].day, users[i].month, users[i].year,
                users[i].username, users[i].balance, users[i].status);
    }
    fclose(file);
}

// Kiem tra tinh hop ly cua thong tin nguoi dung
int isValidUser(User newUser) {
    // Ki?m tra ID, email, phone, username không du?c trùng nhau
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, newUser.id) == 0) {
            printf("Error: ID '%s' already exists.\n", newUser.id);
            return 0;
        }
        if (strcmp(users[i].email, newUser.email) == 0) {
            printf("Error: Email '%s' already exists.\n", newUser.email);
            return 0;
        }
        if (strcmp(users[i].phone, newUser.phone) == 0) {
            printf("Error: Phone '%s' already exists.\n", newUser.phone);
            return 0;
        }
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("Error: Username '%s' already exists.\n", newUser.username);
            return 0;
        }
    }

    // Kiem tra cac truong hop khong trung
    if (strlen(newUser.id) == 0 || strlen(newUser.name) == 0 || strlen(newUser.email) == 0 || strlen(newUser.phone) == 0 ||
        strlen(newUser.username) == 0) {
        printf("Error: All fields must be filled.\n");
        return 0;
    }

    // Kiem tra do dai ID, phone, email, username hop le
    if (strlen(newUser.id) < 3) {
        printf("Error: ID must be at least 3 characters long.\n");
        return 0;
    }
    if (strlen(newUser.phone) < 10) {
        printf("Error: Phone must be at least 10 characters long.\n");
        return 0;
    }
    if (strlen(newUser.email) < 5) {
        printf("Error: Email must be at least 5 characters long.\n");
        return 0;
    }
    if (strlen(newUser.username) < 5) {
        printf("Error: Username must be at least 5 characters long.\n");
        return 0;
    }

    return 1;
}

// Ham nhap thong tin nguoi dung
void addUser() {
    User newUser;
    printf("\n*** Add a new user ***\n");

    // Nh?p thông tin ngu?i dùng
    while (1) {
        printf("Enter the ID (at least 3 characters): ");
        scanf("%s", newUser.id);
        if (strlen(newUser.id) < 3) {
            printf("Error: ID cannot be less than 3 characters.\n");
        } else {
            break;
        }
    }

    printf("Enter the name: ");
    scanf(" %[^\n]%*c", newUser.name); // Cho phep nhap khoang trong
    printf("Enter the email: ");
    scanf("%s", newUser.email);
    printf("Enter the phone: ");
    scanf("%s", newUser.phone);
    printf("Enter the gender (0 for Male, 1 for Female): ");
    scanf("%d", &newUser.gender);
    printf("Enter the date of birth:\n");
    printf("Enter the day: ");
    scanf("%d", &newUser.day);
    printf("Enter the month: ");
    scanf("%d", &newUser.month);
    printf("Enter the year: ");
    scanf("%d", &newUser.year);
    printf("Enter the username (at least 5 characters): ");
    scanf("%s", newUser.username);
    printf("Enter the balance: ");
    scanf("%lld", &newUser.balance);

    newUser.status = 1; // Mac dinh nguui dung moi là active

    // Kiem tra tinh hop le cua thong tin nguoi dung
    if (!isValidUser(newUser)) {
        printf("Error: Invalid data. Please check your input.\n");
        return;
    }

    // Them nguoi dung vao danh sach
    users[userCount++] = newUser;
    printf("User added successfully!\n");

    // Luu l?i d? li?u vào file
    saveUsersToFile();
}


void showUsers() {
    printf("+--------------+-------------------------+-------------------+-----------------+---------------------------+\n");
    printf("| %-12s | %-23s | %-17s | %-15s | %-25s |\n", "ID", "Ho va Ten", "So dien thoai", "Trang thai", "Email");
    printf("+--------------+-------------------------+-------------------+-----------------+---------------------------+\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-12s | %-23s | %-17s | %-15s | %-25s |\n", users[i].id, users[i].name, users[i].phone, 
               (users[i].status == 1 ? "Active" : "Locked"), users[i].email);
    }
    printf("+--------------+-------------------------+-------------------+-----------------+---------------------------+\n");
}

// Ham tim kiem nguoi dung theo ten
void searchUserByName() {
    char searchTerm[50];
    printf("Enter name or part of name to search: ");
    scanf(" %[^\n]%*c", searchTerm);

    printf("+--------------+-------------------------+-------------------+-----------------+---------------------------+\n");
    printf("| %-12s | %-23s | %-17s | %-15s | %-25s |\n", "ID", "Ho va Ten", "So dien thoai", "Trang thai", "Email");
    printf("+--------------+-------------------------+-------------------+-----------------+---------------------------+\n");

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchTerm) != NULL) { // Tìm ki?m chu?i con trong tên
            printf("| %-12s | %-23s | %-17s | %-15s | %-25s |\n", users[i].id, users[i].name, users[i].phone, 
                   (users[i].status == 1 ? "Active" : "Locked"), users[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("No users found with the name containing '%s'.\n", searchTerm);
    }
}

int adminLogin() {
    char adminEmail[50], adminPassword[50];
    int attempts = 0;

    while (1) {
        printf("Enter admin email: ");
        scanf("%s", adminEmail);
        printf("Enter admin password: ");
        scanf("%s", adminPassword);

        if (strcmp(adminEmail, "adminAccount@gmail.com") == 0 && strcmp(adminPassword, "admin123") == 0) {
            return 1; // Ðang nh?p thành công
        } else {
            attempts++;
            printf("Invalid admin credentials.\n");

            if (attempts >= 4) { //Nhap 4 lan khong duoc thi tu domg thoat
                printf("Too many failed attempts. Exiting...\n");
                exit(1);
            }
        }
    }
}

// menu admin
void adminMenu() {
    while (1) {
        int choice;
        printf("\nAdmin Menu:\n");
        printf("[1] Add A New user.\n");
        printf("[2] Show All users.\n");
        printf("[3] Search User by Name.\n");
        printf("[0] Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                showUsers();
                break;
            case 3:
                searchUserByName();
                break;
            case 0:
                printf("Exiting the program...\n");
                return;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}

int main() {
    readUsersFromFile();  
    int choice;

    printf("\n*** Welcome to the User Management System ***\n");

    // Dang nhap Admin
    if (!adminLogin()) {
        printf("Admin login failed. Exiting...\n");
        return 0;
    }

    adminMenu(); // Vao menu admin
    return 0;
}

