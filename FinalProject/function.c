//Noi di trien khai cac ham 
#include "datatype.h"

int adminLogin() {
    char adminEmail[50], adminPassword[50];
    printf("Enter admin email: ");
    scanf("%s", adminEmail);
    printf("Enter admin password: ");
    scanf("%s", adminPassword);
    
    //so sanh ten tai khoan co phai la adminAccout@gmail.com va mat khau la admin123 khong ?
    if (strcmp(adminEmail, "adminAccout@gmail.com") == 0 && strcmp(adminPassword, "admin123") == 0) {
        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}

int userLogin(char email[], char password[]) {
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);
    
    return 1; 
}

void showUsers() {
    printf("|--------------|-------------------------|-------------------|-----------------|---------------------------|\n");
    printf("| %-12s | %-23s | %-17s | %-15s | %-25s |\n", "ID", "Ho va Ten", "So dien thoai", "Trang thai", "Email");
    printf("|--------------|-------------------------|-------------------|-----------------|---------------------------|\n");
    
    for (int i = 0; i < userCount; i++) {
        printf("| %-12s | %-23s | %-17s | %-15s | %-25s |\n", users[i].id, users[i].name, users[i].phone, 
               (users[i].status == 1) ? "Active" : "Locked", users[i].email);
    }

    printf("|----------------------------------------------------------------------------------------------------------|\n");
}

void showUserDetails() {
    char userId[20];
    printf("Enter the user ID: ");
    scanf("%s", userId);

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, userId) == 0) {
            printf("\nUser Details:\n");
            printf("ID: %s\n", users[i].id);
            printf("Name: %s\n", users[i].name);
            printf("Email: %s\n", users[i].email);
            printf("Phone: %s\n", users[i].phone);
            printf("Gender: %s\n", (users[i].gender == 0) ? "Male" : "Female");
            printf("Date of Birth: %d/%d/%d\n", users[i].day, users[i].month, users[i].year);
            printf("Username: %s\n", users[i].username);
            printf("Balance: %lld\n", users[i].balance);
            printf("Status: %s\n", (users[i].status == 1) ? "Active" : "Locked");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No user found with ID: %s\n", userId);
    }
}

void addUser() {
    User newUser;
    printf("\n*** Add a new user ***\n");
    
    while (1) {
        printf("Enter the ID (over 3 characters) : ");
        scanf("%s", newUser.id);
        if (strlen(newUser.id) < 3) {
            printf("Error: ID can not be less than 3 characters.\n");
        } else {
            break;
        }
    }
    
    printf("Enter the name: ");
    scanf(" %[^\n]%*c", newUser.name); // To allow spaces
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
    printf("Enter the username(1 word): ");
    scanf("%s", newUser.username);
    printf("Enter the balance: ");
    scanf("%lld", &newUser.balance);
    
    newUser.status = 1; // New user is active by default
    
    users[userCount++] = newUser;
    printf("User added successfully!\n");
}

void lockUnlockUser() {
    char id[20];
    printf("\n*** Lock (Unlock) an user ***\n");
    printf("Enter a user ID: ");
    scanf("%s", id);
    
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0) {
            found = 1;
            printf("User found for ID: %s\n", id);
            if (users[i].status == 1) {
                printf("Current status: Active\n");
                printf("Do you want to lock this user? (Yes(y) or No(n)): ");
            } else {
                printf("Current status: Locked\n");
                printf("Do you want to unlock this user? (Yes(y) or No(n)): ");
            }

            char choice;
            scanf(" %c", &choice);
            
            if (choice == 'y') {
                // Lock or unlock user based on current status
                users[i].status = (users[i].status == 1) ? 0 : 1; // Toggle status
                if (users[i].status == 1) {
                    printf("User unlocked successfully!\n");
                } else {
                    printf("User locked successfully!\n");
                }
            } else {
                printf("Operation canceled.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("No user found with ID: %s\n", id);
    }
}

void showUserGuideline(int language) {
    if (language == 1) { 
        printf("\n*** Huong Dan Su Dung ***\n");
        printf("1. De them moi mot nguoi dung, nhap thong tin cua ho khi duoc yeu cau.\n");
        printf("2. De xem chi tiet mot nguoi dung, cung cap ID cua ho.\n");
        printf("3. De khoa hoac mo khoa nguoi dung, cung cap ID cua ho va chon thao tac.\n");
        printf("4. Hay chac chan rang tat ca thong tin la chinh xac va duoc cap nhat.\n");
        printf("5. De biet them chi tiet hoac tro giup, vui long lien he voi chung toi qua email: support@bank.com.\n");
        
    } else { 
        printf("\n*** User Guideline ***\n");
        printf("1. To add a new user, enter their details when prompted.\n");
        printf("2. To view a user's details, provide their user ID.\n");
        printf("3. To lock or unlock a user, provide their user ID and choose the operation.\n");
        printf("4. Ensure all information is accurate and up-to-date.\n");
        printf("5. For any issues, contact support at support@bank.com.\n");
    }
}

void aboutUs(int language) {
    if (language == 1) { 
        printf("\n*** Gioi Thieu Chung ***\n");
        printf("He thong Quan Ly Tai Khoan Ngan Hang nay duoc phat trien boi Cong Ty XYZ.\n");
        printf("De biet them chi tiet, vui long truy cap website cua chung toi: www.xyzbank.com.\n");
        printf("Dich vu khach hang: support@bank.com\n");
        
    } else { 
        printf("\n*** About Us ***\n");
        printf("This Bank Management System was developed by XYZ Company.\n");
        printf("For more information, visit our website at www.xyzbank.com.\n");
        printf("Customer service: support@bank.com\n");
    }
}

void adminMenu() {
    while (1) {
    	int language;
        printf("\nAdmin Menu:\n");
        printf("[1] Add a new user.\n");
        printf("[2] Show all users.\n");
        printf("[3] Show detail an user.\n");
        printf("[4] Lock (Unlock) an user.\n");
        printf("[5] User guideline.\n");
        printf("[6] About us.\n");
        printf("[0] Exit the program.\n");
        printf("Enter your choice: ");
        int choice;
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                showUsers();
                break;
            case 3:
            	showUserDetails();
			    break;        
            case 4:
                lockUnlockUser();
                break;
            case 5:
            	printf("Choose your language (Vietnamese = 1; English = 0): ");
            	scanf("%d", &language);
			    showUserGuideline(language);
			    break;
			case 6:
			    printf("Choose your language (Vietnamese = 1; English = 0): ");
            	scanf("%d", &language);
            	aboutUs(language);
			    break;
            case 0:
                printf("Exiting the program...\n");
                printf("========= Thank You =========\n");
                printf("========= See you soon ======\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void userMenu() {
    printf("\nUser Menu:\n");
    // Define user-specific options here
    printf("This is where user-specific options would go.\n");
}
