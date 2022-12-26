#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int ADMIN_ROLE = 0;
const int USER_ROLE = 1;

struct user {
    char login[10];
    char password[10];
    int role; //0 - Admin, 1 - Student
};

struct student {
    int destination[16];
    int departureDay[16];
    int departureMonth[16];
    int departureYear[10];
    float mark;
    int math;
    int physics;
    int programming;
    int english;
    int databases;
};

struct user users[100];
int users_num = 0;

struct student students[100];
int students_num = 0;

void showMessage(char *msg) {
    int i;
    while (1) {
        system("cls");
        printf("%s\n", msg);
        printf("Enter 0 to return:");
        scanf("%d", &i);
        if (i == 0) {
            return;
        }
    }

}

int load() {
    FILE *f = fopen("db.dat", "rb");
    if (f) {
        fread(&users_num, sizeof(int), 1, f);
        fread(&students_num, sizeof(int), 1, f);
        if (users_num > 100 || students_num > 100) {
            //todo: check file size == sizeof(int) * 2 + users_num * sizeof(struct user) + students_num * sizeof(struct student)
            printf("Invalid file format");
            exit(0);
        }
        if (users_num > 0) {
            fread(users, sizeof(struct user), users_num, f);
        }
        if (students_num > 0) {
            fread(students, sizeof(struct student), students_num, f);
        }
        fclose(f);
        return 1;
    }
    return 0;
}

void save() {
    FILE *f = fopen("db.dat", "wb");
    fwrite(&users_num, sizeof(int), 1, f);
    fwrite(&students_num, sizeof(int), 1, f);
    if (users_num > 0) {
        fwrite(users, sizeof(struct user), users_num, f);
    }
    if (students_num > 0) {
        fwrite(students, sizeof(struct student), students_num, f);
    }
    fclose(f);
}

int findUser(char login[10]) {
    for (int i = 0; i < users_num; i++) {
        if (strcmp(users[i].login, login) == 0) {
            return i;
        }
    }
    return -1;
}

void doUserList() {
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        for (int i = 0; i < users_num; i++) {
            printf("%d. %s / %s (%s)\n", i + 1, users[i].login, users[i].password,
                   users[i].role == ADMIN_ROLE ? "admin" : "student");
        }
        printf("Enter 0 to return:");
        int i;
        scanf("%d", &i);
        if (i == 0) {
            return;
        }
    }
}

void doAddUser() {
    system("cls");
    fflush(stdin);//clear input

    struct user u;
    printf("Enter login: ");
    scanf("%s", u.login);
    printf("Enter password: ");
    scanf("%s", u.password);
    printf("Enter role (0 - Admin, 1 - User): ");
    scanf("%d", &u.role);
    if (u.role != 0) {
        u.role = 1;
    }
    users[users_num++] = u;

    showMessage("User added");
}

void doRemoveUser() {
    system("cls");
    fflush(stdin);//clear input

    char login[100];
    printf("Enter login to remove: ");
    scanf("%s", login);
    int index = findUser(login);
    if (index < 0) {
        return;
    }
    printf("Are you sure you want to remove this user? (1 - yes, 0 - No):");
    int i;
    scanf("%d", &i);
    if (i != 0) {
        for (int i = index; i < users_num - 1; i++) {
            users[i] = users[i + 1];
        }
        users_num--;
        showMessage("User removed");
    }
}

void doUsers() {
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        printf("0. Return\n");
        printf("1. List users\n");
        printf("2. Add user\n");
        printf("3. Remove user\n");
        int i;
        printf("Select item: ");
        scanf("%d", &i);
        switch (i) {
            case 0:
                return;
            case 1:
                doUserList();
                break;
            case 2:
                doAddUser();
                break;
            case 3:
                doRemoveUser();
                break;
        }
    }
}

void doListStudents() {
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        printf("+--+----------------+----------------+----------------+----------+----+----+-------+--+----+------------+-------------+\n");
        printf("| N|     Destination|  Departure Date|  Departure time|  Arraival Date|  Arraival Time|Cost|Tickets Left|Tickets Sold|\n");
        printf("+--+----------------+----------------+----------------+----------+----+----+-------+--+----+------------+-------------+\n");
        for (int i = 0; i < students_num; i++) {
            struct student st = students[i];
            printf("|%2d|%16s|%16s|%16s|%10s|%4.1f|   %d|      %d|          %d|      %d|        %d|\n",
                   i + 1, st.destination, st.departureDay, st.departureMonth, st.departureYear, st.mark, st.math, st.physics,
                   st.programming, st.english, st.databases);
        }
        printf("+--+----------------+----------------+----------------+----------+----+----+----------+-----+-----------+-------------+\n");
        printf("Enter 0 to return:");
        int i;
        scanf("%d", &i);
        if (i == 0) {
            return;
        }
    }
}

void doAddStudent() {
    system("cls");
    fflush(stdin);//clear input

    struct student st;
    printf("Enter destinarion: ");
    scanf("%s", st.destination);
    printf("Enter departure day: ");
    scanf("%s", st.departureDay);
    printf("Enter departure month: ");
    scanf("%s", st.departureMonth);
    printf("Enter departure year: ");
    scanf("%s", st.departureYear);
    printf("Enter mark: ");
    scanf("%f", &st.mark);
    printf("Enter Math subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.math);
    if (st.math != 0) {
        st.math = 1;
    }
    printf("Enter Physics subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.physics);
    if (st.physics != 0) {
        st.physics = 1;
    }
    printf("Enter Programming subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.programming);
    if (st.programming != 0) {
        st.programming = 1;
    }
    printf("Enter English subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.english);
    if (st.english != 0) {
        st.english = 1;
    }
    printf("Enter Databases subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.databases);
    if (st.databases != 0) {
        st.databases = 1;
    }
    students[students_num++] = st;
    showMessage("Student added");
}

void doEditStudent() {
    system("cls");
    fflush(stdin);//clear input

    int num;
    printf("Enter student number to edit: ");
    scanf("%d", &num);
    if (num > students_num) {
        return;
    }
    struct student st;

    printf("Enter destination: ");
    scanf("%s", st.destination);
    printf("Enter departure day: ");
    scanf("%s", st.departureDay);
    printf("Enter departure month: ");
    scanf("%s", st.departureMonth);
    printf("Enter departure year: ");
    scanf("%s", st.departureYear);
    printf("Enter mark: ");
    scanf("%f", &st.mark);
    printf("Enter Math subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.math);
    if (st.math != 0) {
        st.math = 1;
    }
    printf("Enter Physics subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.physics);
    if (st.physics != 0) {
        st.physics = 1;
    }
    printf("Enter Programming subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.programming);
    if (st.programming != 0) {
        st.programming = 1;
    }
    printf("Enter English subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.english);
    if (st.english != 0) {
        st.english = 1;
    }
    printf("Enter Databases subscription (1 - yes, 0 - No): ");
    scanf("%d", &st.databases);
    if (st.databases != 0) {
        st.databases = 1;
    }
    students[num - 1] = st;
    showMessage("Student edited");
}

void doRemoveStudent() {
    system("cls");
    fflush(stdin);//clear input

    int num;
    printf("Enter student number to remove: ");
    scanf("%d", &num);
    if (num > students_num) {
        return;
    }
    printf("Are you sure you want to remove this user? (1 - yes, 0 - No):");
    int i;
    scanf("%d", &i);
    if (i != 0) {
        int index = num - 1;
        for (int i = index; i < students_num - 1; i++) {
            students[i] = students[i + 1];
        }
            students_num--;
        showMessage("Student removed");
    }

}

void doStudents() {
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        printf("0. Return\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Edit student\n");
        printf("4. Remove student\n");
        int i;
        printf("Select item: ");
        scanf("%d", &i);
        switch (i) {
            case 0:
                return;
            case 1:
                doListStudents();
                break;
            case 2:
                doAddStudent();
                break;
            case 3:
                doEditStudent();
                break;
            case 4:
                doRemoveStudent();
                break;
        }
    }
}

struct subscription {
    char course[11];
    int members_count;
};

int compareSubscriptions(const void *a, const void *b) {
    return ((struct subscription *) b)->members_count - ((struct subscription *) a)->members_count;
}

int compareStudents(const void *a, const void *b) {
    return ((struct student *) b)->mark - ((struct student *) a)->mark;
}

void doCourse(char course[11]) {
    struct student sorted_students[students_num];
    int num = 0;
    for (int i = 0; i < students_num; ++i) {
        if ((strcmp(course, "Math") == 0 && students[i].math == 1)
            || (strcmp(course, "Physics") == 0 && students[i].physics == 1)
            || (strcmp(course, "Programming") == 0 && students[i].programming == 1)
            || (strcmp(course, "English") == 0 && students[i].english == 1)
            || (strcmp(course, "Databases") == 0 && students[i].databases == 1)) {
            sorted_students[num++] = students[i];
        }
    }
    qsort(sorted_students, num, sizeof(struct student), compareStudents);
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        printf("Student of course %s: \n", course);
        for (int i = 0; i < num && i < 15; i++) {
            struct student st = sorted_students[i];
            printf("%d. %s %s %s (%.1f)\n", i + 1, st.destination, st.departureDay, st.departureMonth, st.mark);
        }
        printf("Enter 0 to return:");
        int i;
        scanf("%d", &i);
        if (i == 0) {
            return;
        }
    }
}

void doCourses() {
    struct subscription subscriptions[5] = {
            {"Math",        0},
            {"Physics",     0},
            {"Programming", 0},
            {"English",     0},
            {"Databases",   0}
    };
    for (int i = 0; i < students_num; i++) {
        subscriptions[0].members_count += students[i].math;
        subscriptions[1].members_count += students[i].physics;
        subscriptions[2].members_count += students[i].programming;
        subscriptions[3].members_count += students[i].english;
        subscriptions[4].members_count += students[i].databases;
    }
    qsort(subscriptions, 5, sizeof(struct subscription), compareSubscriptions);
    while (1) {
        system("cls");
        fflush(stdin);//clear input

        printf("0. Return\n");
        for (int i = 0; i < 5; i++) {
            printf("%d. %s (%d)\n", i + 1, subscriptions[i].course, subscriptions[i].members_count);
        }
        int i;
        printf("Select item: ");
        scanf("%d", &i);
        switch (i) {
            case 0:
                return;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                doCourse(subscriptions[i - 1].course);
                break;

        }
    }
}

void doAdmin() {
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        printf("1. Users\n");
        printf("2. Students\n");
        printf("3. Courses\n");
        printf("4. Exit\n");
        int i;
        printf("Select item: ");
        scanf("%d", &i);
        switch (i) {
            case 1:
                doUsers();
                break;
            case 2:
                doStudents();
                break;
            case 3:
                doCourses();
                break;
            case 4:
                return;
        }
    }
}

void doUser() {
    while (1) {
        system("cls");
        fflush(stdin);//clear input
        printf("1. Students\n");
        printf("2. Courses\n");
        printf("3. Exit\n");
        int i;
        printf("Select item: ");
        scanf("%d", &i);
        switch (i) {
            case 1:
                doListStudents();
                break;
            case 2:
                doCourses();
                break;
            case 3:
                return;
        }
    }
}

void doLogin() {
    char login[100];
    char password[100];
    printf("Login: ");
    scanf("%s", login);
    int i = findUser(login);
    if (i < 0) {
        printf("User not found");
        return;
    }
    struct user u = users[i];
    printf("Password: ");
    scanf("%s", password);
    if (strcmp(u.password, password) != 0) {
        printf("Invalid password");
        return;
    }
    if (u.role == ADMIN_ROLE) {
        doAdmin();
    } else {
        doUser();
    }
}

void createDefaultAdmin() {
    system("cls");
    fflush(stdin);//clear input

    struct user u = {"admin", "pass", ADMIN_ROLE};
    users[users_num++] = u;

    printf("New database with default admin created. Use 'admin' for login and 'pass' for password\n");
}

int main(void) {
    if (load()) {
        //file loaded successfully
        doLogin();
    } else {
        //file doesn't exist
        createDefaultAdmin();
    }
    save();
}
