#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 100

struct Account{
    char accountId[20];    
    char fullName[50];
    char phone[15];
    double balance;
    int status;
};

struct Transaction{
    char tranId[20];
    char senderId[20];
    char receiverId[20];
    double amount;
    char type[10];
    char date[20];
};

int isNumber(char s[]) {
    for(int i = 0; s[i] != '\0' && s[i] != '\n'; i++){
        if(s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

int isLetter(char s[]) {
    for(int i = 0; s[i] != '\0'; i++){
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == ' ')) {
            return 0;  
        }
    }
    return 1; 
}

void strToLower(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = tolower((unsigned char)s[i]); 
    }
}

void space(char str[]) {
    int start = 0;
    while (str[start] == ' '){
    	start++; 
	} 

    int end = strlen(str) - 1;
    while (end >= start && str[end] == ' '){
    	end--;
	}  
 	int index = 0;
    for (int i = start; i <= end; i++) {
        str[index++] = str[i];
    }

    str[index] = '\0';
}

double inputBalance(double oldBalance) {
    char input[50];
    double value;

    while (1) {
        printf("Nhap so du : ", oldBalance);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; 

        if (strlen(input) == 0) {
            return oldBalance; 
        }

        if (sscanf(input, "%lf", &value) != 1) {
            printf("Gia tri khong hop le! Vui long nhap lai.\n");
            continue;
        }

        if (value < 0) {
            printf("So du khong duoc am! Vui long nhap lai.\n");
            continue;
        }

        return value;
    }
}

void create_new_account(struct Account accounts[], int i){
    if(i >= MAX_ACCOUNTS){
        printf("Tao tai khoan that bai!!!!");
        return;
    }
    
    snprintf(accounts[i].accountId, sizeof(accounts[i].accountId), "B25DTCN%03d", i + 1);
    printf("Ma tai khoan : %s\n", accounts[i].accountId);

    while(1){
        printf("Moi ban nhap ten: ");
        fgets(accounts[i].fullName, sizeof(accounts[i].fullName), stdin);
        accounts[i].fullName[strcspn(accounts[i].fullName, "\n")] = '\0';
        
        space(accounts[i].fullName);
        
        if(strlen(accounts[i].fullName) == 0){
            printf("Vui long nhap ten!\n");
    	}else if(!isLetter(accounts[i].fullName)){
    		printf("loi, vui long nhap lai!\n");
        }else{
        	break;
		} 
    }

    while(1){
    printf("Moi ban nhap so dien thoai: ");
    char temp[20];
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    
    space(temp);
    
    if(strlen(temp) == 0){
        printf("Vui long nhap SDT!\n");
        continue;
    }
    
    if(!isNumber(temp)){
        printf("SDT khong hop le!\n");
        continue; 
    }

    int found = 0;
    for(int j = 0; j < i; j++){
        if(strcmp(accounts[j].phone, temp) == 0){
            found = 1;
            break;
        }
    }

    if(found){
        printf("SDT da ton tai, Vui long nhap lai.\n");
        continue; 
    }

    strcpy(accounts[i].phone, temp);
    break; 
}

    
    accounts[i].balance = 0.0;
    accounts[i].status  = 1;
    
    printf("Tao tai khoan thanh cong!!!\n");
}

void update_account(struct Account accounts[], int size){
    char searchId[20];
    int flag = -1;

    while(1){
        printf("Nhap ID tai khoan can cap nhat: ");
        fgets(searchId, sizeof(searchId), stdin);
        searchId[strcspn(searchId, "\n")] = '\0'; 
        
        space(searchId);

        if(strlen(searchId) == 0){
            printf("ID trong, vui long nhap lai!\n");
            continue;
        }

        flag = -1;
        for(int i = 0; i < size; i++){
            if(strcmp(accounts[i].accountId, searchId) == 0){
                flag = i;
                break;
            }
        }

        if(flag == -1){
            printf("Khong tim thay tai khoan, vui long nhap lai!\n");
        } else {
        	break;
		} 
    }

    printf("Cap nhat tai khoan: %s\n", accounts[flag].accountId);
    printf("Ten cu: %s\n", accounts[flag].fullName);
    printf("SDT cu: %s\n", accounts[flag].phone);
    printf("so du cu : %.3f\n", accounts[flag].balance);

    while(1){
        char newName[50];
        printf("Cap nhat ten moi : ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';

        if(strlen(newName) == 0){  
            break;
        } else if(!isLetter(newName)){
            printf("Loi, vui long nhap lai!\n");
        } else {
            strcpy(accounts[flag].fullName, newName);
            break;
        }
    }

    while(1){
        char newPhone[20];
        printf("Cap nhat SDT moi : ");
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = '\0';

        if(strlen(newPhone) == 0){  
            break;
        }

        if(!isNumber(newPhone)){
            printf("lpi, vui long nhap lai!\n");
            continue;
        }

        int duplicate = 0;
        for(int i = 0; i < size; i++){
            if(i != flag && strcmp(accounts[i].phone, newPhone) == 0){
                duplicate = 1;
                break;
            }
        }

        if(duplicate){
            printf("SDT da ton tai, vui long nhap lai!\n");
        } else {
            strcpy(accounts[flag].phone, newPhone);
            break;
        }
    }
    
    accounts[flag].balance = inputBalance(accounts[flag].balance);

    printf("Cap nhat thanh cong!\n");
}


void lock_unlock_account(struct Account accounts[], int size){
    char searchId[20];
    char confirm;
    int found = -1;

    while (1) {
        printf("Nhap ID tai khoan: ");
        fgets(searchId, sizeof(searchId), stdin);
        searchId[strcspn(searchId, "\n")] = '\0';

        if(strlen(searchId) == 0){
            printf("ID khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        found = -1;
        for (int i = 0; i < size; i++) {
            if (strcmp(accounts[i].accountId, searchId) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("Khong tim thay tai khoan! Vui long nhap lai.\n");
        } else {
            break; 
        }
    }

    if(accounts[found].status == 1){
        printf("Tai khoan %s dang hoat dong . Ban co muon khoa khong? (Y/N): ", accounts[found].accountId);
    } else {
        printf("Tai khoan %s dang khoa . Ban co muon mo khoa khong? (Y/N): ", accounts[found].accountId);
    }

    while (1) {
        scanf(" %c", &confirm);
        getchar(); 
        if(confirm == 'Y' || confirm == 'y'){
            accounts[found].status = 1 - accounts[found].status; 
            if(accounts[found].status == 1)
                printf("Tai khoan %s da mo khoa thanh cong!\n", accounts[found].accountId);
            else
                printf("Tai khoan %s da duoc khoa thanh cong!\n", accounts[found].accountId);
            break;
        } else if(confirm == 'N' || confirm == 'n'){
            printf("Huy thao tac.\n");
            break;
        } else {
            printf("Lua chon khong hop le! Nhap Y hoac N: ");
        }
    }
}

void search_account(struct Account accounts[], int size) {
    char keyword[50];

    while (1) {
        printf("Nhap tu khoa tim kiem (ID hoac Ten): ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; 

        if (strlen(keyword) == 0) {
            printf("Tu khoa khong duoc de trong, vui long nhap lai!\n");
            continue;
        }
        break;
    }

    char lowerKeyword[50];
    strcpy(lowerKeyword, keyword);
    strToLower(lowerKeyword);

    printf("\n=== Ket qua tim kiem ===\n");

    int found = 0;

    for (int i = 0; i < size; i++) {
        char lowerName[50], lowerId[20];

        strcpy(lowerName, accounts[i].fullName);
        strToLower(lowerName);

        strcpy(lowerId, accounts[i].accountId);
        strToLower(lowerId);

        if (strstr(lowerId, lowerKeyword) != NULL ||
            strstr(lowerName, lowerKeyword) != NULL) {

            printf("ID: %-5s | Ten: %-20s | Phone: %-15s | Balance: %-10.3f | Status: %-10s\n",
                   accounts[i].accountId,
                   accounts[i].fullName,
                   accounts[i].phone,
                   accounts[i].balance,
                   accounts[i].status ? "dang hoat dong" : "dang khoa");

            found = 1;
        }
    }

    if (!found) {
        printf("Khong co ket qua phu hop!\n");
    }
}

void list_accounts_pagination(struct Account accounts[], int size) {
    if (size == 0) {
        printf("Danh sach tai khoan trong!\n");
        return;
    }

    int page_size = 5; 	

    int total_pages = (size + page_size - 1) / page_size;
    int current_page = 1;

    char choice;

    while (1) {
        int start = (current_page - 1) * page_size;
        int end = start + page_size;
        if (end > size) end = size;

        printf("\n====== DANH SACH TAI KHOAN - TRANG %d/%d ======\n", current_page, total_pages);
        printf("||%-5s | %-15s | %-20s | %-15s | %-12s | %-10s ||\n",
               "STT", "Account ID", "Full Name", "Phone", "Balance", "Status");
        printf("||=============================================================================================||\n");

        for (int i = start; i < end; i++) {
            printf("||%-5d | %-15s | %-20s | %-15s | %-12.2f | %-10s ||\n",
                   i + 1,
                   accounts[i].accountId,
                   accounts[i].fullName,
                   accounts[i].phone,
                   accounts[i].balance,
                   accounts[i].status == 1 ? "Active" : "Locked");
        }

        printf("\n[ A ] Trang sau");
        printf("   [ D ] Trang truoc");
        printf("   [ G ] Nhap so trang");
        printf("   [ E ] Thoat\n");
        printf("Nhap lua chon: ");
        scanf(" %c", &choice);

        if (choice == 'A' || choice == 'a') {
            if (current_page < total_pages)
                current_page++;
            else
                printf("Ban dang o trang cuoi!\n");
        }
        else if (choice == 'D' || choice == 'd') {
            if (current_page > 1)
                current_page--;
            else
                printf("Ban dang o trang dau!\n");
        }
        else if (choice == 'G' || choice == 'g') {
            int go;
            printf("Nhap so trang muon den: ");
            scanf("%d", &go);
            if (go >= 1 && go <= total_pages)
                current_page = go;
            else
                printf("So trang khong hop le!\n");
        }
        else if (choice == 'E' || choice == 'e') {
            printf("Thoat phan trang...\n");
            break;
        }
        else {
            printf("Lua chon khong hop le!\n");
        }
    }
}



void swapAccount(struct Account accounts[], int i, int j) {
    struct Account temp = accounts[i];
    accounts[i] = accounts[j];
    accounts[j] = temp;
}

void sortByName(struct Account accounts[], int size) {
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(strcmp(accounts[j].fullName, accounts[j+1].fullName) > 0){
                swapAccount(accounts, j, j+1);
            }
        }
    }
}

void sortByBalance(struct Account accounts[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(accounts[j].balance < accounts[j+1].balance){
                swapAccount(accounts, j, j+1);
            }
        }
    }
}

void sort_accounts(struct Account accounts[], int size){
    if(size == 0){
        printf("Danh sach rong, khong the sap xep!\n");
        return;
    }

    int choice;

    while (1) {
        printf("1. Sap xep theo Ten (A-Z)\n");
        printf("2. Sap xep theo So du (Giam dan)\n");
        printf("Nhap lua chon: ");

        if (scanf("%d", &choice) != 1) {
            printf("Nhap sai! Vui long nhap lai.\n");
            while(getchar() != '\n'); 
            continue;
        }

        getchar();

        if(choice == 1){
            sortByName(accounts, size);
            printf("Da sap xep theo Ten (A-Z)!\n");
            break;

        } else if(choice == 2){
            sortByBalance(accounts, size);
            printf("Da sap xep theo So du (Giam dan)!\n");
            break;

        } else {
            printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    }

    list_accounts_pagination(accounts, size);
}





int main(){    
    struct Account accounts[MAX_ACCOUNTS];
    int accountCount = 0;
    int choice;
    char input[10];
    
    do{
        printf("==========Mini Banking System=========\n");
        printf("||     1. Them tai khoan moi        ||\n");
        printf("||     2. Cap nhat thong tin        ||\n");
        printf("||     3. Quan ly trang thai        ||\n");
        printf("||     4. Tra cuu tai khoan         ||\n");
        printf("||     5. Danh sach tai khoan       ||\n");
        printf("||     6. Sap xep danh sach         ||\n");
        printf("||     7. Giao dich chuyen khoan    ||\n");
        printf("||     8. Lich su giao dich         ||\n"); 
        printf("||     9. Thoat!!!                  ||\n");
        printf("======================================\n");

       while (1) {
        printf("Moi ban nhap chuc nang: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("Khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        int isNumber = 1;
        for (int i = 0; i < strlen(input); i++) {
            if (input[i] < '0' || input[i] > '9') {
                isNumber = 0;
                break;
            }
        }

        if (!isNumber) {
            printf("Vui long nhap so!\n");
            continue;
        }

        choice = atoi(input);

        if (choice < 1 || choice > 9) {
            printf("Chuc nang khong hop le, vui long nhap lai.\n");
            continue;
        }

        break;  
    }
        
        switch(choice){
            case 1 :
                create_new_account(accounts, accountCount);
                accountCount++;
                break;

            case 2 :
                update_account(accounts, accountCount);
                break;

            case 3 :
                lock_unlock_account(accounts, accountCount);
                break;

            case 4 : 
                search_account(accounts, accountCount);
                break;
                
            case 5 :
    			list_accounts_pagination(accounts, accountCount);
    			break;
    			
    		case 6 :
    			sort_accounts(accounts, accountCount);
        		break;

            case 9 :
                printf("Thoat!!!\n");
                break;

            default : 
                printf("Vui long lua chon lai.\n");
                break;
        }
        
    }while(choice != 9);
    
    return 0;
}
