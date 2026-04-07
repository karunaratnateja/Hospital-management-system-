#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char doctor[50];
};

void addPatient();
void displayPatients();
void searchPatient();
void updatePatient();
void deletePatient();

int main() {
    int choice;

    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add Patient Record\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch(choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    fflush(stdin);
    printf("Enter Name: ");
    gets(p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    fflush(stdin);
    printf("Enter Gender: ");
    gets(p.gender);
    printf("Enter Disease: ");
    gets(p.disease);
    printf("Enter Doctor Assigned: ");
    gets(p.doctor);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    printf("Patient record added successfully!\n");
}

void displayPatients() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    while (fread(&p, sizeof(p), 1, fp)) {
        printf("\nID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\n",
               p.id, p.name, p.age, p.gender, p.disease, p.doctor);
    }
    fclose(fp);
}

void searchPatient() {
    int id;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    int found = 0;
    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\n",
                   p.id, p.name, p.age, p.gender, p.disease, p.doctor);
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient not found!\n");
    fclose(fp);
}

void updatePatient() {
    int id;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    fflush(stdin);

    int found = 0;
    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Enter New Name: ");
            gets(p.name);
            printf("Enter New Age: ");
            scanf("%d", &p.age);
            fflush(stdin);
            printf("Enter New Gender: ");
            gets(p.gender);
            printf("Enter New Disease: ");
            gets(p.disease);
            printf("Enter New Doctor: ");
            gets(p.doctor);

            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            printf("Patient record updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient not found!\n");
    fclose(fp);
}

void deletePatient() {
    int id;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(p), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        printf("Patient record deleted successfully!\n");
    else
        printf("Patient not found!\n");
}
