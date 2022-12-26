#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int ADMIN_ROLE = 0;
const int USER_ROLE = 1;

struct user {
  char login[10];
  char password[10];
  int role;  //0 - Admin, 1 - User
};

struct ticket {
  int numberOfTrain;       //номер поезда
  char destination[50];    //пункт назначения
  int departureDay[50];       //дату отправления
  int departureMonth[50];
  int departureYear[50];
  int departureHour;      //время отправления
  int departureMinute;
  int departureSecond;
  int arrivalDay;        //время прибытия на конечный пункт
  int arrivalMonth;
  int arrivalYear;
  int arrivalHour;
  int arrivalMinute;
  int arrivalSecond;
  double ticketPrice;  //стоимость одного билета
  int quantityOfRemainingTickets;  //количество оставшихся для продажи билетов
  int quantityOfSoldTickets;  //количество проданных билетов
};

struct user users[100];  //переменная users, хранящая список пользователей
int users_num = 0;      //переменная, хранящая количество пользователей  

struct ticket tickets[100];    //переменная users, хранящая список билетов
int tickets_num = 0;          ////переменная, хранящая количество билетов 
 
int load(void) {
  FILE *file = fopen("test.txt", "rb");  //открываем файл для чтения
    if (file) {
    fread(&users_num, sizeof(int), 1, file);  
    fread(&tickets_num, sizeof(int), 1, file);

    if (users_num > 100 || tickets_num > 100) {
      printf("Invalid file format");
      exit(0);
    }
    if (users_num > 0) {
      fread(users, sizeof(struct user), users_num, file);
    }
    if (tickets_num > 0) {
      fread(tickets, sizeof(struct ticket), tickets_num, file);
    }
    fclose(file);  //закрываем файл 
    return 1;
  }
  return 0;
}

void save(void) {
  FILE *file = fopen("test.txt", "wb");   //открываем файл для записи
  fwrite(&users_num, sizeof(int), 1, file);
  fwrite(&tickets_num, sizeof(int), 1, file);
  if (users_num > 0) {
    fwrite(users, sizeof(struct user), users_num, file);
  }
  if (tickets_num > 0) {
    fwrite(tickets, sizeof(struct ticket), tickets_num, file);
  }
  fclose(file);   //закрываем файл
}

int findUser(char login[10]) {
  for (int i = 0; i < users_num; i++){
    if (strcmp(users[i].login, login) == 0) {
      return i;
    }
  }
  return -1;
}


void doUserList(void) {
  while (1) {
    system("cls");  //clear screen console
	fflush(stdin);  //clear input
    for (int i = 0; i < users_num; i++) {
      printf("%d. %s / %s (%s)\n", i + 1, users[i].login, users[i].password,
        users[i].role == ADMIN_ROLE ? "admin" : "user");
    }
    printf("Enter 0 to return: ");
    int i;
    scanf("%d", &i);
    if (i == 0) {
      return;
    }
  }
}

void doAddUser(void) {
  system("cls");   //clear screen console
  fflush(stdin);  //clear input	  
  struct user u;
  printf("Enter login: ");
  scanf("%s", &u.login);
  printf("Enter password: ");
  scanf("%s", &u.password);
  printf("Enter role (0 - Admin, 1 - User): ");
  scanf("%d", &u.role);
  if (u.role != 0) {
    u.role = 1;
  }
  users[users_num++] = u;
  printf("User added");
}

void doDeleteUser(void) {
  system("cls");
  fflush(stdin);
  char login[100];
  printf("Enter login to delete: ");
  scanf("%s", &login);
  int index = findUser(login);
  if (index < 0) {
    return;
  }
  printf("Are you sure you want to delete this user? (1 - Yes, 0 - No): ");
  int i;
  scanf("%d", &i);
  if (i != 0) {
  	for (int i = index; i < users_num - 1; i++) {
  	  users[i] = users[i + 1];
	}
	users_num--;
	printf("User deleted");
  }
}

void doUsers(void) {
  while (1) {
  	system("cls");
  	fflush(stdin);
  	printf("0. Return\n");
  	printf("1. List users\n");
  	printf("2. Add users\n");
  	printf("3. Delete user\n");
  	int i;
  	printf("Select number: ");
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
  	  	doDeleteUser();
  	  	break;
	}
  }
}

void doListTickets() {
    while (1) {
        system("cls");  //clear screen console
        fflush(stdin); //clear input
        printf("+--+----------------+----------------+----------------+----------------+---------------+---------------+------+------------+-------------+\n");
        printf("| N| Nunmer Of Train|     Destination|  Departure Date|  Departure time|  Arraival Date|  Arraival Time| Cost |Tickets Left| Tickets Sold|\n");
        printf("+--+----------------+----------------+----------------+----------------+---------------+---------------+------+------------+-------------+\n");
        for (int i = 0; i < tickets_num; i++) {
            struct ticket t = tickets[i];
            printf("|%2d|%16d|%16s|%16d.%d.%d|%16d.%d.%d|%10d.%d.%d|%d.%d.%d| %dBYN|      %d|          %d|\n", i + 1, t.numberOfTrain, t.destination, 
			    t.departureDay, t.departureMonth, t.departureYear, t.departureHour, t.departureMinute, t.departureSecond,
				t.arrivalDay, t.arrivalMonth, t.arrivalYear, t.arrivalHour, t.arrivalMinute, t.arrivalSecond, t.ticketPrice,
				t.quantityOfRemainingTickets, t.quantityOfSoldTickets);
        }
        printf("+--+----------------+----------------+----------------+----------------+---------------+---------------+------+------------+-------------+\n");
        printf("Enter 0 to return:");
        int i;
        scanf("%d", &i);
        if (i == 0) {
            return;
        }
    }
}

void doAddTicket(void) {
  system("cls");  //clear screen console
  fflush(stdin);  //clear input
  struct ticket t;
  printf("Enter number of train: ");
  scanf("%d", &t.numberOfTrain);
  printf("Enter destination: ");
  scanf("%s", &t.destination);
  printf("Enter departure day: ");
  scanf("%d", &t.departureDay);
  printf("Enter departure month: ");
  scanf("%d", &t.departureMonth);
  printf("Enter departure year: ");
  scanf("%d", &t.departureYear);
  printf("Enter departure hour: ");
  scanf("%d", &t.departureHour);
  printf("Enter departure minute: ");
  scanf("%d", &t.departureMinute);
  printf("Enter departure second: ");
  scanf("%d", &t.departureSecond);
  printf("Enter arrival day: ");
  scanf("%d", &t.arrivalDay);
  printf("Enter arrival month: ");
  scanf("%d", &t.arrivalMonth);
  printf("Enter arrival year: ");
  scanf("%d", &t.arrivalYear);
  printf("Enter arrival hour: ");
  scanf("%d", &t.arrivalHour);
  printf("Enter arrival minute: ");
  scanf("%d", &t.arrivalMinute);
  printf("Enter arrival second: ");
  scanf("%d", &t.arrivalSecond);
  printf("Enter ticket price: ");
  scanf("%f", &t.ticketPrice);
  printf("Enter quantity of remaining tickets: ");
  scanf("%d", &t.quantityOfRemainingTickets);
  printf("Enter quantity of sold tickets: ");
  scanf("%d", &t.quantityOfSoldTickets);
  printf("Ticket added");
}

void doEditTicket(void) {
  system("cls");  //clear screen console
  fflush(stdin);  //clear input
  int num;
  printf("Enter ticket number to edit: ");
  scanf("%d", &num);
  if (num > tickets_num) {
  	return;
  }
  struct ticket t;
  printf("Enter number of train: ");
  scanf("%s", &t.numberOfTrain);
  printf("Enter destination: ");
  scanf("%s", &t.destination);
  printf("Enter departure day: ");
  scanf("%d", &t.departureDay);
  printf("Enter departure month: ");
  scanf("%d", &t.departureMonth);
  printf("Enter departure year: ");
  scanf("%d", &t.departureYear);
  printf("Enter departure hour: ");
  scanf("%d", &t.departureHour);
  printf("Enter departure minute: ");
  scanf("%d", &t.departureMinute);
  printf("Enter departure second: ");
  scanf("%d", &t.departureSecond);
  printf("Enter arrival day: ");
  scanf("%d", &t.arrivalDay);
  printf("Enter arrival month: ");
  scanf("%d", &t.arrivalMonth);
  printf("Enter arrival year: ");
  scanf("%d", &t.arrivalYear);
  printf("Enter arrival hour: ");
  scanf("%d", &t.arrivalHour);
  printf("Enter arrival minute: ");
  scanf("%d", &t.arrivalMinute);
  printf("Enter arrival second: ");
  scanf("%d", &t.arrivalSecond);
  printf("Enter ticket price: ");
  scanf("%f", &t.ticketPrice);
  printf("Enter quantity of remaining tickets: ");
  scanf("%d", &t.quantityOfRemainingTickets);
  printf("Enter quantity of sold tickets: ");
  scanf("%d", &t.quantityOfSoldTickets);
}

void doDeleteTicket(void) {  
  system("cls");  //clear screen console
  fflush(stdin);  //clear input 
  int num;
  printf("Enter ticket number to delete: ");
  scanf("%d", &num);
  if (num > tickets_num) { 
    return;
  } 
  printf("Are you sure you want to delete this ticket? (1 - Yes, 2 - No): ");
  int i;
  scanf("%d", &i);
  if (i != 0) {
  	int index = num - 1;
  	for (int i = index; i < tickets_num - 1; i++) {
  	  tickets[i] = tickets[i + 1];
	}
	tickets_num--;
	printf("Ticket deleted");
  }
}

void doSortTickets(void) {
  int count;
  struct ticket *t;
  system("cls");  //clear screen console
  fflush(stdin);  //clear input 
  for (int j = 0; j < count; j++) {
  	for (int i = 0; i < count - 1; i++) {
  	  if (strcmp(t[i].destination, t[i + 1].destination) > 0) {  //сортировка по пункту назначения
  	    struct ticket temp;  //временная переменная
  	    temp = t[i];            //сортировка пузырьком
  	    t[i] = t[i + 1];
  	    t[i + 1] = temp;
	  }
	}
  }
}

void doTickets(void) {
  while(1) {
  	system("cls");  //clear screen console
  	fflush(stdin);  //clear input
  	printf("0. Return\n");
  	printf("1. List tickets\n");
  	printf("2. Add ticket\n");
  	printf("3. Edit ticket\n");
  	printf("4. Delete ticket\n");
  	printf("5. Sort tickets\n");
  	int i;
  	printf("Select number: ");
  	scanf("%d", &i);
  	switch (i) {
  	  case 0:
  	  	return;
  	  case 1:
  	  	doListTickets();
  	  	break;
  	  case 2:
  	  	doAddTicket();
  	  	break;
  	  case 3:
  	  	doEditTicket();
  	  	break;
  	  case 4:
  	  	doDeleteTicket();
  	  	break;
  	  case 5:
  	  	doSortTickets();
  	  	break;
	}
  }
}

void doBuyTicket(void) {
  system("cls");  //clear screen console
  fflush(stdin);  //clear input 
  int count;
  struct ticket tickets[100];
  printf("Enter destination: ");
  char city[50];
  scanf("%s", &city);
  printf("Enter from what time (hour) do you need a ticket: ");
  int hour1;
  scanf("%d", &hour1);
  printf("Enter until what time (hour) do you need a ticket: ");
  int hour2;
  scanf("%d", &hour2);
  printf("\n+--+----------------+----------------+----------------+----------------+---------------+---------------+------+------------+-------------+\n");
  printf("| N| Nunmer Of Train|     Destination|  Departure Date|  Departure time|  Arraival Date|  Arraival Time| Cost |Tickets Left| Tickets Sold|\n");
  printf("+--+----------------+----------------+----------------+----------------+---------------+---------------+------+------------+-------------+\n");      
  for (int i = 0; i < count; i++) {      //цикл для всех билетов на поезда
  	if (strcmp(tickets[i].destination, city) == 0 &&                //проверка билета
	    tickets[i].departureHour >= hour1 && tickets[i].arrivalHour < hour2) {
	      printf("%3d|", i);  //вывод подходящего билета
		} 
  }
  printf("Enter which ticket do you want to buy: ");  //запрос на покупку билета
  int numberOfTicket;
  scanf("%d", &numberOfTicket); 
  if (numberOfTicket < 0 || numberOfTicket >= count) {      //проверка введённого билета 
    printf("Error");  
	exit(1);
  }
    //проверка: остались ли билеты
  if (tickets[numberOfTicket].quantityOfSoldTickets < tickets[numberOfTicket].quantityOfRemainingTickets) {
  	tickets[numberOfTicket].quantityOfSoldTickets++;
  	printf("You bought a ticket\n");
  }
  else
    printf("Unfortunately, tickets ran out");  
}

void doAdmin(void) {
  while (1) {
  	system("cls");  //clear screen console
  	fflush(stdin);  //clear input
  	printf("1. Users\n");
  	printf("2. Tickets\n");
  	printf("3. Exit\n");
  	int i;
  	printf("Select number: ");
  	scanf("%d", &i);
  	switch (i) {
  	  case 1:
  	  	doUsers();
  	  	break;
  	  case 2:
  	  	doTickets();
  	  	break;
  	  case 3:
  	  	return;
	}
  }
}

void doUser(void) {
  while (1) {
    system("cls");  //clear screen console
    fflush(stdin);  //clear input
    printf("1. List tickets\n");
    printf("2. Buy ticket\n");
    printf("3. Exit\n");
    int i;
    printf("Select number: ");
    scanf("%d", &i);
    switch (i) {
      case 1:
      	doListTickets();
      	break;
      case 2:
        doBuyTicket();
      	break;
      case 3:
      	return;
	}
  }
}

void doLogin(void) {
  char login[100];
  char password[100];
  printf("Login: ");
  scanf("%s", &login);
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
  }
  else {
  	doUser();
  }
}

void createDefaultAdmin(void) {
  system("cls");
  fflush(stdin);  //clear input
  struct user u = {"admin", "pass", ADMIN_ROLE};
  users[users_num++] = u;
  printf("New datebase with default admin created. Use 'admin' for login and 'pass' for password\n");
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