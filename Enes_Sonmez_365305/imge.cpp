#include "imge.h"
#include "helper.h"
#include "hu_moments.h"

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

	// read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

BYTE* ConvertToIntensity(BYTE* Buffer, int width, int height)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	BYTE* newbuf = new BYTE[width * height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11 * Buffer[bufpos + 2] + 0.59 * Buffer[bufpos + 1] + 0.3 * Buffer[bufpos]);
		}

	return newbuf;
}//ConvetBMPToIntensity

unsigned int* Histogram(BYTE* Raw_Intensity, int width, int height) {
	int ptr = 0;
	int size = width * height;
	unsigned int* histData = new unsigned int[256]{ 0 };

	while (ptr < size) {
		int h = Raw_Intensity[ptr];
		histData[h] +=1;
		ptr++;
	}
	return histData;
}

BYTE* KMeansThreshold(BYTE* Raw_Intensity, int width, int height, int k) {
	unsigned int* hist = Histogram(Raw_Intensity, width, height);
	int size = width * height;
	BYTE* tempBuffer = new BYTE[size];
	int* color;

	double* cluster_means = new double[k] {0};
	double* cluster_sum = new double[k] {0};
	double* cluster_count = new double[k] {0};
	
	// Oluþturulan deðerler baþlangýç deðerine setlenir ve cluster means'lere rastgele sayýlar atanýr.
	srand(time(0));
	for (int i = 0; i < k; i++) {
		cluster_means[i] = int(rand() % 256);
	}

	int isEqual = 0;
	double epsilon = 0.001;
	while (isEqual != k) {
		isEqual = 0;
		for (int point = 0; point < 256; point++) {
			double min_distance = DBL_MAX;
			int min_cluster = 0;
			for (int cluster = 0; cluster < k; cluster++) {
				const double distance = abs(point - cluster_means[cluster]); // Fonlsiyona dönüþtürülecek
				if (distance < min_distance) {
					min_distance = distance;
					min_cluster = cluster;
				}
			}
			cluster_sum[min_cluster] += hist[point] * point;
			cluster_count[min_cluster] += hist[point];
		}

		for (int i = 0; i < k; i++) {
			if (cluster_count[i] != 0) { // NaN deðer gelince sonsuz döngüye giriyor.
				const double tempMeans = cluster_sum[i] / cluster_count[i];
				const double distance = abs(tempMeans - cluster_means[i]);
				if (distance < epsilon) {
					isEqual++;
				}
				cluster_means[i] = tempMeans;
				cluster_sum[i] = 0;
				cluster_count[i] = 0;
			}
			else {
				cluster_means[i] = int(rand() % 256);
			}
		}
	}

	if (k == 2) {
		color = new int[2]{ 0,255 };
	}
	else {
		color = new int[k];
		for (int i = 0; i < k; i++) {
			color[i] = int(rand() % 256);
		}
	}

	// Kmeans deðerlerine göre; gray to binary
	for (int i = 0; i < size; i++) {
		double min_distance = DBL_MAX;
		int min_cluster = 0;
		for (int cluster = 0; cluster < k; cluster++) {
			const double distance = abs(Raw_Intensity[i] - cluster_means[cluster]); // Fonlsiyona dönüþtürülecek
			if (distance < min_distance) {
				min_distance = distance;
				min_cluster = cluster;
			}
		}
		tempBuffer[i] = color[min_cluster];
	}

	return tempBuffer;
}

BYTE* InvertBinaryImage(BYTE* Binary_Image, int width, int height) {
	int size = width * height;
	BYTE* tempBuffer = new BYTE[size];
	for (int i = 0; i < size; i++)
	{
		if (Binary_Image[i] == 255) tempBuffer[i] = 0;
		else tempBuffer[i] = 255;
	}
	return tempBuffer;
}

BYTE* Labeling(BYTE* Binary_Image, int width, int height, int& total_label) {
	int size = width * height;
	BYTE* labeledImage = new BYTE[size]{ 0 };
	int locate = 0;

	// First Pass
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			locate = i * width + j;
			int point = Binary_Image[locate];
			int leftNeighbour = 0;
			int topNeighbour = 0;

			if (point != 0) {
				if ((i - 1) * width + j >= 0) topNeighbour = labeledImage[(i - 1) * width + j];
				if ((i * width + (j - 1)) - width * i >= 0) leftNeighbour = labeledImage[(i * width + (j - 1))];

				if (leftNeighbour == 0 && topNeighbour == 0) {
					labeledImage[locate] = total_label;
					total_label++;
				}
				else if ((leftNeighbour == 0 && topNeighbour != 0) || leftNeighbour == topNeighbour) {
					labeledImage[locate] = topNeighbour;
				}
				else if (leftNeighbour != 0 && topNeighbour == 0) {
					labeledImage[locate] = leftNeighbour;
				}
				else {
					// Two Pass (Collesion)
					int low, high = 0;
					if (leftNeighbour < topNeighbour) {
						low = leftNeighbour;
						high = topNeighbour;
					}
					else
					{
						low = topNeighbour;
						high = leftNeighbour;
					}
					labeledImage[locate] = low;
					total_label--;

					for (int i = 0; i < locate; i++)
					{
						if (labeledImage[i] == high)
							labeledImage[i] = low;
						if (labeledImage[i] > high)
							labeledImage[i]--;
					}
				}
			}
		}

	return labeledImage;
}

struct Boxes* Segment(BYTE* Labeled_Image, int width, int height, int totalLabel) {
	int size = width * height;
	Boxes* objects = new Boxes[totalLabel];

	for (int label = 0; label < totalLabel; label++)
	{
		int tempSize = 0;
		for (int i = 0; i < size; i++)
			if (label + 1 == Labeled_Image[i]) tempSize++;

		int* rowIndex = new int[tempSize];
		int* columnIndex = new int[tempSize];
		int ptr = 0;
		for (int point = 0; point < size; point++) {
			if (Labeled_Image[point] == label + 1) {
				columnIndex[ptr] = point % width;
				rowIndex[ptr] = (point - columnIndex[ptr]) / width;
				ptr++;
			}
		}

		objects[label].top_row = Min(rowIndex, tempSize);
		objects[label].top_col = Min(columnIndex, tempSize);
		objects[label].bottom_row = Max(rowIndex, tempSize);
		objects[label].bottom_col = Max(columnIndex, tempSize);
		objects[label].box_width = objects[label].bottom_col - objects[label].top_col + 1;
		objects[label].box_height = objects[label].bottom_row - objects[label].top_row + 1;
		objects[label].label = label + 1;
	}

	return objects;
}

BYTE* Erosion(BYTE* Binary_Image, int width, int height, MASK* mask) {
	int erosionWidth = (width + 2 * (mask->width / 2)); // Mask size'ýna göre padding ekleme
	int erosionHeight = (height + 2 * (mask->height / 2));
	int erosionSize = erosionWidth * erosionHeight;

	BYTE* tempErosionImage = new BYTE[erosionSize]{ 0 };
	BYTE* ErosionImage = new BYTE[erosionSize]{ 0 };

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tempErosionImage[(i + mask->height / 2) * (erosionWidth) + j + mask->width / 2] = Binary_Image[i * width + j];
		}
	}
	
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {

			int point = (row + mask->height / 2) * (erosionWidth)+col + mask->width / 2;

			if (tempErosionImage[point] == 255)
			{
				int startRow = row - (mask->height / 2);
				int startCol = col - (mask->width / 2);
				int areTheyAllOne = 1;

				for (int i = startRow; i < startRow + mask->height; i++) {
					for (int j = startCol; j < startCol + mask->width; j++) {
						int index = i * erosionWidth + j;
						if (tempErosionImage[index] == 0) {
							ErosionImage[point] = 0;
							areTheyAllOne = 0;
						}
					}
				}
				if (areTheyAllOne) ErosionImage[point] = 255;
			}
		}
	}
	BYTE* binary = new BYTE[width * height]{ 0 };
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			binary[i * width + j] = ErosionImage[(i + mask->height / 2) * erosionWidth + j + mask->width / 2];
	
	return binary;
}

BYTE* Dilation(BYTE* Binary_Image, int width, int height, MASK* mask) {
	int dilationWidth = (width + 2 * (mask->width / 2)); // Mask size'ýna göre padding ekleme
	int dilationHeight = (height + 2 * (mask->height / 2));
	int dilationSize = dilationWidth * dilationHeight;

	BYTE* tempdilationImage = new BYTE[dilationSize]{ 0 };
	BYTE* dilationImage = new BYTE[dilationSize]{ 0 };

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tempdilationImage[(i + mask->height / 2) * (dilationWidth)+j + mask->width / 2] = Binary_Image[i * width + j];
		}
	}

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {

			//int point = row * dilationWidth + col;
			int point = (row + mask->height / 2) * (dilationWidth)+col + mask->width / 2;
			if (tempdilationImage[point] == 255)
			{
				int startRow = row - (mask->height / 2);
				int startCol = col - (mask->width / 2);

				for (int i = startRow; i < startRow + mask->height; i++) {
					for (int j = startCol; j < startCol + mask->width; j++) {
						int index = i * dilationWidth + j;
						dilationImage[index] = 255;
					}
				}
			}
		}
	}
	BYTE* binary = new BYTE[width * height]{ 0 };
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			binary[i * width + j] = dilationImage[(i + mask->height / 2) * dilationWidth + j + mask->width / 2];

	return binary;
}

BYTE* Opening(BYTE* Binary_Image, int width, int height, MASK* mask) {
	BYTE* erosion = Erosion(Binary_Image, width, height, mask);
	BYTE* opening = Dilation(Binary_Image, width, height, mask);
	return opening;
}

BYTE* ClosingMorphology(BYTE* Binary_Image, int width, int height, MASK* mask) {
	BYTE* dialtion = Dilation(Binary_Image, width, height, mask);
	BYTE* closing = Erosion(Binary_Image, width, height, mask);
	return closing;
}

double* FeatureExtract(Boxes* Objects, BYTE* Binary_Image, int num_box, int width) {
	double* centerOfGravity = new double[7]{ 0 };

	int temp_total_label = (num_box);
	for (int i = 0; i < num_box; i++) {
		Boxes object = Objects[i];

		int tempSize = object.box_width * object.box_height; // Obje image'leri oluþturulur.
		BYTE* Object_Image = new BYTE[tempSize]{ 0 };
		int ptr = 0;
		for (int i = object.top_row; i <= object.bottom_row; i++)
		{
			for (int j = object.top_col; j <= object.bottom_col; j++)
			{
				Object_Image[ptr] = Binary_Image[i * width + j];
				ptr++;
			}
		}

		myHuMoments* huMoments = new myHuMoments(Object_Image, object.box_width, object.box_height);
		double* fiMoments = huMoments->getHuMoments();
		//huMoments->logTransform();
		if (!isinf(fiMoments[0]) && !isnan(fiMoments[0]) && !isinf(fiMoments[1]) && !isnan(fiMoments[1])
			&& !isinf(fiMoments[2]) && !isnan(fiMoments[2]) && !isinf(fiMoments[3]) && !isnan(fiMoments[3])
			&& !isinf(fiMoments[4]) && !isnan(fiMoments[4]) && !isinf(fiMoments[5]) && !isnan(fiMoments[5])
			&& !isinf(fiMoments[6]) && !isnan(fiMoments[6])) {

			for (int j = 0; j < 7; j++) {
				centerOfGravity[j] += abs(fiMoments[j]);
			}
		}
		else {
			temp_total_label -= 1;
		}
		delete[] Object_Image;
	}

	for (int j = 0; j < 7; j++) {
		centerOfGravity[j] /= temp_total_label;
	}

	return centerOfGravity;
}

void SaveDatabase(DB_MOMENT* db, int db_moment_count, double* moments, char* text)
{
	db[db_moment_count].fiMoments = moments;
	db[db_moment_count].labelName = text;
	db[db_moment_count].id = db_moment_count;
}

PREDICTION* Testing(Boxes* Objects, BYTE* Binary_Image, DB_MOMENT* db, int db_member_count, int num_box, int width) {
	PREDICTION* results = new PREDICTION[num_box];

	for (int i = 0; i < num_box; i++) {
		Boxes object = Objects[i];

		int tempSize = object.box_width * object.box_height; // Obje image'leri oluþturulur.
		BYTE* Object_Image = new BYTE[tempSize]{ 0 };
		int ptr = 0;
		for (int i = object.top_row; i <= object.bottom_row; i++)
		{
			for (int j = object.top_col; j <= object.bottom_col; j++)
			{
				Object_Image[ptr] = Binary_Image[i * width + j];
				ptr++;
			}
		}

		myHuMoments* huMoments = new myHuMoments(Object_Image, object.box_width, object.box_height);
		double* fiMoments = huMoments->getHuMoments();

		for (int k = 0; k < 7; k++) {
			fiMoments[k] = abs(fiMoments[k]);
		}
		double min_distance = DBL_MAX;
		char* name;
		int id = 0;
		for (int j = 0; j < db_member_count; j++) {
			double l1 = ManhattanDistance(db[j].fiMoments, fiMoments, 7);

			if (l1 < min_distance) {
				min_distance = l1;
				name = db[j].labelName;
				id = db[j].id;
			}
		}
		results[i].distance = min_distance;
		results[i].name = name;
		results[i].id = id;
		delete[] Object_Image;
	}

	return results;
}