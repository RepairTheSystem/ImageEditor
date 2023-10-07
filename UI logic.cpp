// инициализация файла
cout << "Enter file name (without .bmp): ";
string file_name;

cin >> file_name;
file_name = "C://CODE//C++//ImageEditor//" + file_name + ".bmp";

ifstream img(file_name, ios::binary);
ofstream new_img("C://CODE//C++//ImageEditor//new_img.bmp", ios::binary | ios::trunc);

// проверка на корректность ввода
if (!img.is_open())
{
    cout << "Error with oppening file" << endl;
    return 0;
}

// работаем с заголовком
BMPHeader header;

img.read(reinterpret_cast<char *>(&header), sizeof(header));

int width = header.width;
int height = header.height;

// вектор хранения пикселей
vector<pixel_struct> pix(width *height);

img.read(reinterpret_cast<char *>(pix.data()), pix.size() * 3);

// логика интерфейса пользователя
char command1;
cout << "Enter command to rotate " << endl;
cout << "1 - rotating 90 degrees right, 2 - rotating 90 degrees left, 0 - without rotating ";
cin >> command1;

if (command1 == '1')
    rotate_right(pix, header);
else if (command1 == '2')
    rotate_left(pix, header);

int radius;
cout << "Enter Gauss blur level " << endl;
cout << "(if u dont need blur enter 0, else integer) ";
cin >> radius;

if (radius != 0)
    gauss(pix, width, height, radius);

// записываем данные в новый файл
new_img.write(reinterpret_cast<char *>(&header), sizeof(header));
new_img.write(reinterpret_cast<char *>(pix.data()), pix.size() * 3);

cout << "Image succelful write in 'new_img.bmp'." << endl;

img.close();
new_img.close();
