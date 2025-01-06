#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char id[15];
    char name[50];
    char email[50];
    char phone[15];
    char status[10];
}User;

User users[100];
int userCount = 0;

void mainMenu();
void loginAdmin();
void adminMenu();
void addUser();
void displayAllUsers();
void searchUser();
void searchUserById();
int isUnique(char id[], char email[], char phone[]);
int isUserInfoValid(char id[], char name[], char phone[]);
int isUserInfoNotEmpty(char id[], char name[], char email[], char phone[]);
void toggleUserStatus();
void sortUsersByName();
void loginUser();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    while(1) {
        printf("\n*** User Management System ***\n");
        printf("          CHOOSE YOUR ROLE\n");
        printf("      ========================\n");
        printf("      [1] Admin\n");
        printf("      [2] User\n");
        printf("      [0] Exit the Program\n");
        printf("      ========================\n");
        printf("      Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                loginAdmin();
                break;
            case 2:
                loginUser(); // Nhap case 2 cua menuAdmin truoc, thi moi hien thi duoc thong tin User
                break;
            case 0:
            	printf("\n");
            	printf("    ========= Thank You =========\n");
            	printf("    ========= See You Soon ======\n");
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}

void loginAdmin() {
    char email[50], password[50];
    printf("\n*** User Management System ***\n");
    printf("               LOGIN\n");
    printf("      ========================\n");
    printf("      Email: ");
    scanf("%s", email);
    printf("      Password: ");
    scanf("%s", password);
    if(strcmp(email, "adminAccount@gmail.com") == 0 && strcmp(password, "admin123") == 0) {
        adminMenu();
    } else {
        printf("Email hoac mat khau khong hop le\n");
    }
}

void loginUser() { // Dang nhap nguoi dung
    char input[50];
    printf("\n*** User Login ***\n");
    printf("Nhap ID Hoac Email De Dang Nhap: ");
    while (getchar() != '\n');  // Dam bao xoa bo dem
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // Xoa ky tu \n neu co

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, input) == 0 || strcmp(users[i].email, input) == 0) {
            found = 1;
            printf("\nThong tin nguoi Dung:\n");
            printf("ID: %s\n", users[i].id);
            printf("Ten: %s\n", users[i].name);
            printf("Email: %s\n", users[i].email);
            printf("So �ien Thoai: %s\n", users[i].phone);
            printf("Trang Thai: %s\n", users[i].status);
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay nguoi dung voi ID hoac Email '%s'.\n", input);
    }
}

void adminMenu() {
    int choice;
    while(1) {
        printf("\n*** Admin Menu ***\n");
        printf("  ========================\n");
        printf("  [1] Add A New User\n");
        printf("  [2] Show ALL Users\n");
        printf("  [3] Search Users\n");
        printf("  [4] Search Users By Id\n");
        printf("  [5] Lock/Open User\n");
        printf("  [6] Sort Users By Name\n");
        printf("  [0] Exit\n");
        printf("  ========================\n");
        printf("  Enter Your Choice: ");
        scanf("%d", &choice);
        system("cls");

        switch(choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayAllUsers(); //Hien thi cac user duoc nhap vao
                break;
            case 3:
                searchUser(); //Nhap case 2 truoc thi moi hoat dong duoc
                break;
            case 4:
                searchUserById(); //Nhap case 2 truoc thi moi hoat dong duoc
                break;
            case 5:    
                toggleUserStatus(); //Nhap case 2 truoc thi moi hoat dong duoc
				break;
			case 6:
                sortUsersByName(); //Nhap case 2 truoc thi moi hoat dong duoc
                break;	
            case 0:
                return;
            default:
                printf("Lua Chon Khong Hop Le\n");
        }
    }
}

void addUser(){ //case 1
    if (userCount >= 100) {
        printf("Danh Sach Da Day\n");
        return;
    }
    User newUser;
    fflush(stdin);
    printf("\n*** Add New User ***\n");
    printf("Enter user ID (over 3 characters) : ");
    fgets(newUser.id, sizeof(newUser.id), stdin);
    newUser.id[strcspn(newUser.id, "\n")] = 0;
    fflush(stdin);
    printf("Enter user name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
    fflush(stdin);
    printf("Enter user email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;
    fflush(stdin);
    printf("Enter user phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;
    fflush(stdin);
    printf("Status (Open/Lock): ");
    fgets(newUser.status, sizeof(newUser.status), stdin);
    newUser.status[strcspn(newUser.status, "\n")] = 0;

    if (!isUserInfoNotEmpty(newUser.id, newUser.name, newUser.email, newUser.phone)) {
        return;
    }

    if (isUserInfoValid(newUser.id, newUser.name, newUser.phone) && isUnique(newUser.id, newUser.email, newUser.phone)) {
        users[userCount++] = newUser;
        FILE *file = fopen("user.txt", "a");
        if (file == NULL) {
            printf("Loi: Khong the mo file de ghi\n");
            return;
        }
        fprintf(file, "%s,%s,%s,%s,%s\n", newUser.id, newUser.name, newUser.email, newUser.phone, newUser.status);
        fclose(file);
        printf("Them Thanh Cong\n");
    } else {
        printf("Loi: ID hoac Email Hoac Phone Bi Trung. Nguoi Dung Khong Duoc Them Vao\n");
    }

    printf("\nPress any key to return to Admin Menu... ");
    getchar(); 
}

void displayAllUsers(){ //case 2
    userCount = 0;
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("Khong The Mo File user.txt\n");
        return;
    }

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%s\n",
                  users[userCount].id,
                  users[userCount].name,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].status) == 5) {
        userCount++;
        if (userCount >= 100) {
            printf("Danh Sach Da Day\n");
            break;
        }
    }
    fclose(file);

    if (userCount == 0) {
        printf("Khong Co Nguoi Dung\n");
        return;
    }

    printf("\n============================================================================================================\n");
    printf("| %-12s | %-25s | %-30s | %-15s | %-10s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-12s | %-25s | %-30s | %-15s | %-10s |\n",
               users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }

    printf("============================================================================================================\n");
}

void searchUser() { //case 3
    char searchName[50];
    printf("Nhap Ten De Tim Kiem: ");
    while (getchar() != '\n');
    scanf(" %[^\n]", searchName);

    int found = 0;
    printf("\n------------------------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-25s | %-30s | %-15s | %-10s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName) != NULL) {
            found = 1;
            printf("| %-12s | %-25s | %-30s | %-15s | %-10s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("------------------------------------------------------------------------------------------------------------\n");

    if (!found) {
        printf("Khong Tim Thay Nguoi Dung '%s'\n", searchName);
    }
}


void searchUserById() { //case 4
    char searchId[50];
    printf("Nhap ID De Tim Kiem: ");
    while (getchar() != '\n');
    scanf(" %[^\n]", searchId);

    int found = 0;
    printf("\n------------------------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-25s | %-30s | %-15s | %-10s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].id, searchId) != NULL) {
            found = 1;
            printf("| %-12s | %-25s | %-30s | %-15s | %-10s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
        }
    }
    printf("------------------------------------------------------------------------------------------------------------\n");

    if (!found) {
        printf("Khong Tim Thay Nguoi Dung ID %s\n", searchId);
    }
}

int isUnique(char id[], char email[], char phone[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0 || strcmp(users[i].email, email) == 0 || strcmp(users[i].phone, phone) == 0) {
            return 0;
        }
    }
    return 1;
}

//gioi han nhap
int isUserInfoValid(char id[], char name[], char phone[]) {
    if (strlen(id) < 3 || 
        strlen(name) <= 3 ||
        strlen(phone) != 10) {
        printf("Thong tin khong hop le. ID nguoi dung phai dai 3 ky tu tro len, Ten phai nhieu hon 3 ky tu, So dien thoai phai dai 10 ky tu.\n");
        return 0;
    }
    return 1;
}

int isUserInfoNotEmpty(char id[], char name[], char email[], char phone[]) {
    if (strlen(id) == 0 || strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0) {
        printf("Thong tin nguoi dung khong duoc de trong. Vui long nhap lai.\n");
        return 0;
    }
    return 1;
}

void toggleUserStatus(){ //case 5
    char userId[15];
    printf("Nhap ID Nguoi Dung De Lock/Unlock: ");
    scanf("%s", userId);
    int userFound = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, userId) == 0) {
            userFound = 1;
            // Toggle the user's status
            if (strcmp(users[i].status, "Open") == 0) {
                strcpy(users[i].status, "Lock");
                printf("User %s Hien Da Bi Khoa\n", users[i].name);
            } else {
                strcpy(users[i].status, "Open");
                printf("User %s Hien Da Duoc Mo Khoa\n", users[i].name);
            }

            FILE *file = fopen("user.txt", "w");
            if (file == NULL) {
                printf("Loi: Khong the mo file de ghi\n");
                return;
            }

            for (int j = 0; j < userCount; j++) {
                fprintf(file, "%s,%s,%s,%s,%s\n",
                        users[j].id, users[j].name, users[j].email, users[j].phone, users[j].status);
            }

            fclose(file);
            return;
        }
    }

    if (!userFound) {
        printf("Khong Tim Thay ID Nguoi Dung\n");
    }
}

void sortUsersByName(){ //case 6
    int choice;
    printf("\n*** Sort Users by Name ***\n");
    printf("1. Sort A to Z \n");
    printf("2. Sort Z to A \n");
    printf("Choose your option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // A -> Z
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].name, users[j].name) > 0) {
                    // Hoan doi cac user[i] v� user[j]
                    User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("Danh Sach Nguoi Dung Da Duoc Sap Xep Tu A Den Z\n");
    } else if (choice == 2) {
        // Z -> A
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].name, users[j].name) < 0) {
                    // Hoan doi cac user[i] v� user[j]
                    User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("Danh Sach Nguoi Dung Da Duoc Sap Xep Tu Z Den A\n");
    } else {
        printf("Lua Chon Khong Hop Le\n");
        return;
    }

    // Luu du lieu vao file
    FILE *file = fopen("user.txt", "w");  
    if (file == NULL) {
        printf("Loi: Khong the mo file de ghi\n");
        return;
    }

    // Ghi lai danh sach nguoi dung vao file
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }

    fclose(file);

    // Hien thi lai danh sach nguoi dung da sap xep
    displayAllUsers();
}

