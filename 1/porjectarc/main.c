#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 100

struct MedicalTest {
    int patientID;
    char testName[50];
    char testDate[8]; // YYYY-MM
    float result;
};

struct MedicalTest medicalTests[MAX_TESTS];
int testCount = 0;

// Function prototypes
void readTestDataFromFile() {
    FILE *file = fopen("medical_test.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    while (!feof(file)) {
        struct MedicalTest newTest;
        fscanf(file, "%d: %[^,], %s, %f\n", &newTest.patientID, newTest.testName, newTest.testDate, &newTest.result);
        medicalTests[testCount++] = newTest;
    }

    fclose(file);
}

void displayMenu() {
    printf("\nMedical Test Management System Menu\n");
    printf("1. Add a new medical test\n");
    printf("2. Search for a test by patient ID\n");
    printf("3. Search for a test by test name\n");
    printf("4. Search for tests within a specific period\n");
    printf("5. Search for unnormal tests\n");
    printf("6. Calculate average test value\n");
    printf("7. Update an existing test result\n");
    printf("8. Delete a test\n");
    printf("9. Display all tests\n");
    printf("0. Exit\n");
}
void addNewTest() {
    if (testCount >= MAX_TESTS) {
        printf("Cannot add new test. Maximum test limit reached.\n");
        return;
    }

    struct MedicalTest newTest;

    // Input patient ID (must be 7 digits)
    int patientID;
    do {
        printf("Enter patient ID (7 digits): ");
        scanf("%d", &patientID);
        if (patientID < 1000000 || patientID > 9999999) {
            printf("Error: Patient ID must be exactly 7 digits.\n");
        }
    } while (patientID < 1000000 || patientID > 9999999);
    newTest.patientID = patientID;

    printf("Enter test name: ");
    scanf("%s", newTest.testName);

    printf("Enter test date (YYYY-MM): ");
    scanf("%s", newTest.testDate);

    printf("Enter test result: ");
    scanf("%f", &newTest.result);

    // Validate test result based on test name
    if (strcmp(newTest.testName, "Hgb") == 0) {
        if (newTest.result < 13.8 || newTest.result > 17.2) {
            printf("Error: Invalid test result for Hemoglobin test. Result should be between 13.8 and 17.2 grams per deciliter.\n");
            return;
        }
    } else if (strcmp(newTest.testName, "BGT") == 0) {
        if (newTest.result < 70 || newTest.result > 99) {
            printf("Error: Invalid test result for Blood Glucose Test. Result should be between 70 and 99 milligrams per deciliter.\n");
            return;
        }
    } else if (strcmp(newTest.testName, "LDL") == 0) {
        if (newTest.result >= 100) {
            printf("Error: Invalid test result for LDL Cholesterol Test. Result should be less than 100 milligrams per deciliter.\n");
            return;
        }
    } else if (strcmp(newTest.testName, "BPT") == 0) {
        // Assuming systolic and diastolic blood pressure are stored separately in the result field
        float systolicBP = (int)newTest.result;
        float diastolicBP = newTest.result - systolicBP;

        if (systolicBP >= 120 || diastolicBP >= 80) {
            printf("Error: Invalid test result for Blood Pressure Test. Systolic blood pressure should be less than 120 mm Hg and Diastolic blood pressure should be less than 80 mm Hg.\n");
            return;
        }
    } else {
        // Unknown test, no validation
    }

    // Add the new test to the array
    medicalTests[testCount++] = newTest;
    printf("Test added successfully.\n");
}
void searchByPatientID() {
    int searchID;
    printf("Enter patient ID to search: ");
    scanf("%d", &searchID);

    printf("Patient Tests:\n");
    int found = 0;
    for (int i = 0; i < testCount; i++) {
        if (medicalTests[i].patientID == searchID) {
            printf("Test Name: %s, Test Date: %s, Result: %.2f\n",
                   medicalTests[i].testName, medicalTests[i].testDate, medicalTests[i].result);
            found = 1;
        }
    }

    if (!found) {
        printf("No tests found for patient ID %d\n", searchID);
    }
}
void searchByTestName() {
    char searchName[50];
    printf("Enter test name to search: ");
    scanf("%s", searchName);

    printf("Tests for %s:\n", searchName);
    int found = 0;
    for (int i = 0; i < testCount; i++) {
        if (strcmp(medicalTests[i].testName, searchName) == 0) {
            printf("Patient ID: %d, Test Date: %s, Result: %.2f\n",
                   medicalTests[i].patientID, medicalTests[i].testDate, medicalTests[i].result);
            found = 1;
        }
    }

    if (!found) {
        printf("No tests found for test name %s\n", searchName);
    }
}
void searchByTestPeriod() {
    char startDate[8], endDate[8];
    printf("Enter start date (YYYY-MM): ");
    scanf("%s", startDate);
    printf("Enter end date (YYYY-MM): ");
    scanf("%s", endDate);

    printf("Tests between %s and %s:\n", startDate, endDate);
    int found = 0;
    for (int i = 0; i < testCount; i++) {
        if (strcmp(medicalTests[i].testDate, startDate) >= 0 && strcmp(medicalTests[i].testDate, endDate) <= 0) {
            printf("Patient ID: %d, Test Name: %s, Result: %.2f\n",
                   medicalTests[i].patientID, medicalTests[i].testName, medicalTests[i].result);
            found = 1;
        }
    }

    if (!found) {
        printf("No tests found between %s and %s\n", startDate, endDate);
    }
}
void searchUnnormalTests() {
    printf("Searching for unnormal tests:\n");
    int found = 0;

    // Define normal ranges for each test
    float hgbMin = 13.8, hgbMax = 17.2;
    float bgtMin = 70, bgtMax = 99;
    float ldlMax = 100;
    float systolicMax = 120, diastolicMax = 80;

    // Iterate through tests and check if they are unnormal
    for (int i = 0; i < testCount; i++) {
        if (strcmp(medicalTests[i].testName, "Hgb") == 0) {
            if (medicalTests[i].result < hgbMin || medicalTests[i].result > hgbMax) {
                printf("Patient ID: %d, Test Name: %s, Result: %.2f\n",
                       medicalTests[i].patientID, medicalTests[i].testName, medicalTests[i].result);
                found = 1;
            }
        } else if (strcmp(medicalTests[i].testName, "BGT") == 0) {
            if (medicalTests[i].result < bgtMin || medicalTests[i].result > bgtMax) {
                printf("Patient ID: %d, Test Name: %s, Result: %.2f\n",
                       medicalTests[i].patientID, medicalTests[i].testName, medicalTests[i].result);
                found = 1;
            }
        } else if (strcmp(medicalTests[i].testName, "LDL") == 0) {
            if (medicalTests[i].result >= ldlMax) {
                printf("Patient ID: %d, Test Name: %s, Result: %.2f\n",
                       medicalTests[i].patientID, medicalTests[i].testName, medicalTests[i].result);
                found = 1;
            }
        } else if (strcmp(medicalTests[i].testName, "BPT") == 0) {
            // Assuming systolic and diastolic blood pressure are stored separately in the result field
            float systolicBP = (int)medicalTests[i].result;
            float diastolicBP = medicalTests[i].result - systolicBP;

            if (systolicBP >= systolicMax || diastolicBP >= diastolicMax) {
                printf("Patient ID: %d, Test Name: %s, Result: %.2f\n",
                       medicalTests[i].patientID, medicalTests[i].testName, medicalTests[i].result);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No unnormal tests found.\n");
    }
}
void calculateAverage() {
    printf("Average test values:\n");

    // Variables to store total and count for each test
    float totalHgb = 0, totalBgt = 0, totalLdl = 0, totalSystolic = 0, totalDiastolic = 0;
    int countHgb = 0, countBgt = 0, countLdl = 0, countBpt = 0;

    // Iterate through tests and accumulate values for each test type
    for (int i = 0; i < testCount; i++) {
        if (strcmp(medicalTests[i].testName, "Hgb") == 0) {
            totalHgb += medicalTests[i].result;
            countHgb++;
        } else if (strcmp(medicalTests[i].testName, "BGT") == 0) {
            totalBgt += medicalTests[i].result;
            countBgt++;
        } else if (strcmp(medicalTests[i].testName, "LDL") == 0) {
            totalLdl += medicalTests[i].result;
            countLdl++;
        } else if (strcmp(medicalTests[i].testName, "BPT") == 0) {
            // Assuming systolic and diastolic blood pressure are stored separately in the result field
            float systolicBP = (int)medicalTests[i].result;
            float diastolicBP = medicalTests[i].result - systolicBP;
            totalSystolic += systolicBP;
            totalDiastolic += diastolicBP;
            countBpt++;
        }
    }

    // Calculate average for each test type
    if (countHgb > 0) {
        printf("Hgb: %.2f\n", totalHgb / countHgb);
    }
    if (countBgt > 0) {
        printf("BGT: %.2f\n", totalBgt / countBgt);
    }
    if (countLdl > 0) {
        printf("LDL: %.2f\n", totalLdl / countLdl);
    }
    if (countBpt > 0) {
        float avgSystolic = totalSystolic / countBpt;
        float avgDiastolic = totalDiastolic / countBpt;
        printf("BPT: Systolic: %.2f, Diastolic: %.2f\n", avgSystolic, avgDiastolic);
    }
}
void updateTestResult() {
    int patientID;
    char testName[50];
    printf("Enter patient ID: ");
    scanf("%d", &patientID);

    printf("Enter test name: ");
    scanf("%s", testName);

    float newResult;
    printf("Enter new test result: ");
    scanf("%f", &newResult);

    int found = 0;
    for (int i = 0; i < testCount; i++) {
        if (medicalTests[i].patientID == patientID && strcmp(medicalTests[i].testName, testName) == 0) {
            medicalTests[i].result = newResult;
            printf("Test result updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No test found for patient ID %d with test name %s.\n", patientID, testName);
    }
}
void deleteTest() {
    int patientID;
    char testName[50];
    printf("Enter patient ID: ");
    scanf("%d", &patientID);

    printf("Enter test name: ");
    scanf("%s", testName);

    int found = 0;
    for (int i = 0; i < testCount; i++) {
        if (medicalTests[i].patientID == patientID && strcmp(medicalTests[i].testName, testName) == 0) {
            // Shift elements to remove the test
            for (int j = i; j < testCount - 1; j++) {
                medicalTests[j] = medicalTests[j + 1];
            }
            testCount--;
            printf("Test deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No test found for patient ID %d with test name %s.\n", patientID, testName);
    }
}
void displayAllTests() {
    printf("All Medical Tests:\n");
    for (int i = 0; i < testCount; i++) {
        printf("Patient ID: %d, Test Name: %s, Test Date: %s, Result: %.2f\n",
               medicalTests[i].patientID, medicalTests[i].testName, medicalTests[i].testDate, medicalTests[i].result);
    }
}

int main() {
    readTestDataFromFile();

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewTest();
                break;
            case 2:
                searchByPatientID();
                break;
            case 3:
                searchByTestName();
                break;
            case 4:
                searchByTestPeriod();
                break;
            case 5:
                searchUnnormalTests();
                break;
            case 6:
                calculateAverage();
                break;
            case 7:
                updateTestResult();
                break;
            case 8:
                deleteTest();
                break;
            case 9:
                displayAllTests();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number from 0 to 9.\n");
        }
    } while (choice != 0);

    return 0;
}

