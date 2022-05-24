/*
====================================================================================
#		PHẦN MỀM QUẢN LÝ DANH SÁCH LỚP HỌC ĐƯỢC VIẾT BẰNG NGÔNG NGỮ LẬP TRÌNH C 
# Đây là một project nho nhỏ, tổng hợp lại toàn bộ kiến thức cơ bản của mình
# trong quá trình học lập trình C cơ bản. Toàn bộ project này không sử dụng bất kì một
# thư viện cao siêu nào mà, chỉ đơn thuần là những kiến thức cơ bản và cốt lõi của ngôn
# ngữ lập trình C.
#
#									_Tác giả: Vue Thắng_
#
#	Từ vựng tiếng anh
#	Grade: điểm số
#	Maths: toán
#	Physics: Vật lý
#	Chemistry: hóa học
#	History: Lịch sử
#	Geography: Địa lý
#	Literature: văn học
#	Grade point average: điểm trung bình
#	Gender: giới tính
#
=====================================================================================
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

struct Student
{
	char full_name[30];
	char gender[5];
	int age;
	float GPA;
};
typedef struct Student Student;

// Căng chỉnh bảng dữ liệu
void set_With(int w)
{
	int i = 0;

	while (i <= w)
	{
		printf(" "); 
		i++;
	}
}

void student_Infor(Student &hs)
{
	FILE *get_File_Data = fopen("danhsachlop.txt", "r");

	if(!get_File_Data)
	{
		printf("File khong ton tai!!");
		return;
	}

	char str[100];
	
	fgets(str, sizeof(str), get_File_Data);

	char *full_name, *age, *gender, *GPA;

	full_name = strtok(str, ";");
	gender = strtok(NULL, ";");
	age = strtok(NULL, ";");
	GPA = strtok(NULL, ";");

	strcpy(hs.full_name, full_name);
	strcpy(hs.gender, gender);
	hs.age = atoi(age);
	hs.GPA = atof(GPA);
}

void show_Infor(Student hs, int i)
{
	printf("\t\t| %d", i);
	if(i >= 10)
		set_With(1);
	else
		set_With(2);
	printf("| %s", hs.full_name);
	set_With(23 - strlen(hs.full_name));

	printf("| %s", hs.gender);
	set_With(13 - strlen(hs.gender));

	printf("| %d", hs.age);
	set_With(6 - 2);

	printf("| %.1f", hs.GPA);
	if(hs.GPA == 10)
		set_With(9 - 4);
	else
		set_With(9 - 3);
	printf("|\n");
}

struct Node
{
	Student data;
	struct Node *next;
};
typedef struct Node Node;

struct Forward_list
{
	Node *star;
	Node *end;
};
typedef struct Forward_list Forward_list;

// hàm khởi tạo list
void init_List(Forward_list &list)
{
	list.end = list.star = NULL;
}

// Tạo node
Node* get_Node(Student new_data)
{
	Node* temp = (Node*)malloc(sizeof(Node));

	if(temp == NULL)
		return NULL;
	temp->data = new_data;
	temp->next = NULL;
	return temp;
}

// Hàm thêm node vào List
void insert_to_Node(Forward_list &list, Node *p)
{
	if(list.star == NULL)
		list.star = list.end = p;
	else
	{
		for (Node *q = list.star; q != NULL; q = q->next)
		{
			if (q == list.end)
			{
				q->next = p;
				p->next = NULL;
				list.end = p;
				return;
			}
		}
	}
}

// Đẩy từng node vào List.
void push_to_List(Forward_list &list)
{
	Student hs;
	FILE *get_File_Data = fopen("danhsachlop.txt", "r");

	if(!get_File_Data)
	{
		printf("File khong ton tai!!");
		return;
	}

	char str[100];
	
	fgets(str, sizeof(str), get_File_Data);

	while (!feof(get_File_Data))
	{
		char *ho_ten, *tuoi, *gioi_tinh, *diem_tong;
		ho_ten = strtok(str, ";");
		gioi_tinh = strtok(NULL, ";");
		tuoi = strtok(NULL, ";");
		diem_tong = strtok(NULL, ";");

		strcpy(hs.full_name, ho_ten);
		strcpy(hs.gender, gioi_tinh);
		hs.age = atoi(tuoi);
		hs.GPA = atof(diem_tong);

		Node *p = get_Node(hs);
		insert_to_Node(list, p);
		fgets(str, sizeof(str), get_File_Data);
	}
	fclose(get_File_Data);
}

// Ghi dữ liệu vào file
void insert_Data_to_File()
{
	FILE *write_to_File = fopen("danhsachlop.txt", "a");

	if(!write_to_File)
	{
		printf("Mo File khong thanh cong\n");
		getch();
		return;
	}

	char full_name[30], gender[5];
	int age;
	double GPA;

	printf("Ho va ten: ");
	fflush(stdin);
	gets(full_name);

	printf("Gioi tinh: ");
	fflush(stdin);
	gets(gender);

	do{
		printf("Tuoi: ");
		fflush(stdin);
		scanf("%d", &age);
		if(age < 18 || age > 60)
		{
			printf("Nhap tuoi khong hop le!(tuoi <= 18 hoac tuoi <= 60)\n");
		}
	}while(age < 18 || age > 60);

	do{
		printf("Diem tong: ");
		fflush(stdin);
		scanf("%lf", &GPA);
		if(GPA < 0 || GPA > 10)
		{
			printf("Nhap diem khong hop le! Vui long nhap lai\n");
		}
	}while (GPA < 0 || GPA > 10);

	fprintf(write_to_File, "%s;%s;%d;%.2lf\n", full_name, gender,age,GPA);
	fclose(write_to_File);
}

// Hiển thị danh sách
void print_List(Forward_list list)
{
	printf("\n\t\t+--------------------------------------------------------------------+\n");
	printf("\t\t| STT | HO VA TEN\t\t| GIOI TINH\t| TUOI\t | TONG DIEM |\n");
	printf("\t\t+--------------------------------------------------------------------+\n");
	int i = 1;
	for (Node *p = list.star; p != NULL; p = p->next)
	{
		show_Infor(p->data, i);
		i++;
	}
	printf("\t\t+--------------------------------------------------------------------+\n");
}

// Giải phóng bộ nhớ cho List
void free_List(Forward_list &list)
{
	while (list.star != NULL)
	{
		Node *temp = list.star;
		list.star = list.star->next;
		free(temp);
	}
}

// Tìm kiếm một chuỗi có tồn tại trong file hay không
void searching(const char* str, Forward_list list)
{
	for(Node *p = list.star; p != NULL; p = p->next)
	{
		if (strcmpi(str, p->data.full_name) == 0)
		{
			printf("\nHo va ten: %s\n", p->data.full_name);
			printf("\nGioi Tinh: %s\n", p->data.gender);
			printf("\nTuoi: %d\n", p->data.age);
			printf("\nTong diem: %.1lf\n", p->data.GPA);
			return;
		}
	}
	printf("\nKhong ton tai!");
}

// Xóa một node ra khỏi List
void remove_a_Node(const char *str, Forward_list list)
{
	push_to_List(list);

	int check_delete = 0, check_delete_head = 0;

	if(strcmpi(list.star->data.full_name, str) == 0)
	{
		Node *temp = list.star;
		list.star = list.star->next;
		free(temp);
		check_delete_head = 1;
		check_delete = 1;
	}

	if(check_delete_head == 0)
	{
		for(Node *p = list.star; p != list.end; p = p->next)
		{
			if (strcmpi(str, p->next->data.full_name) == 0)
			{
				Node *temp = p->next;
				p->next = p->next->next;
				free(temp);
				check_delete = 1;
				break;
			}
		}
	}

	if(check_delete == 1)
	{
		FILE *Insert_Data_to_File = fopen("danhsachlop.txt", "w");

		if(Insert_Data_to_File == NULL)
		{
			printf("\t\tXOA DU LIEU KHONG THANH CONG!");
			getch();
			return;
		}

		for(Node *p = list.star; p != NULL; p = p->next)
		{
			fprintf(Insert_Data_to_File,"%s;%s;%d;%.2lf\n", p->data.full_name, p->data.gender, p->data.age, p->data.GPA);
		}
		fclose(Insert_Data_to_File);
		printf("\t\tXOA THANH CONG");
	}
	else
		printf("\t\tTEN CAN XOA KHONG TON TAI TRONG DANH SACH");
}

// Hiển thị menu cho người dùng lựa chọn
void show_Menu()
{
	printf("\n\t\t\t CHUONG TRINH QUAN LY HOC SINH C/C++\n");

	printf("\n\t\t-----------------------------------------------");
	printf("\n\t\t [1] In danh sach hoc sinh");
	printf("\n\t\t [2] Them hoc sinh vao danh sach");
	printf("\n\t\t [3] Xoa hoc sinh ra khoi danh sach");
	printf("\n\t\t [4] Tim kiem thong tin");
	printf("\n\t\t [5] Thong ke");
	printf("\n\t\t [0] Thoat chuong trinh");
	printf("\n\t\t-----------------------------------------------\n");
}

int main()
{
	Forward_list list;
	init_List(list);

	while (true)
	{
		show_Menu();
		
		int options = 0;
		printf("\nNhap vao lua chon? ");
		fflush(stdin);
		scanf("%d", &options);

		if(options == 1)
		{
			push_to_List(list);
			printf("\n\t\t\t\tDANH SACH HOC SINH\n");
			print_List(list);
		}
		else if(options == 2)
		{
			insert_Data_to_File();
			printf("\n\t\tBAN THEM XONG");
		}
		else if(options == 3)
		{
			char str[30];
			printf("Nhap ten can xoa: ");
			fflush(stdin);
			gets(str);
			remove_a_Node(str, list);
		}
		else if(options == 4)
		{
			push_to_List(list);
			char str[30];
			printf("Nhap ten can tim kiem: ");
			fflush(stdin);
			gets(str);
			searching(str, list);
		}
		else if(options == 5)
		{
			printf("Tinh nang %d dang duoc phat trien", options);
		}
		else if(options == 0)
		{
			printf("\n\t\tBAN DA THOAT CHUONG TRINH.");
			break;
		}
		free_List(list);
		getch();
		system("cls");
	}
	
	getch();
	return 0;
}