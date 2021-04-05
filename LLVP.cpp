
// @author: Hjinhan

#include<iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <iomanip>
#include <math.h>
#include<time.h>  

using namespace std;
using namespace cv;


///逻辑矢量变换 **********************************************

///** fun函数：4位2个点
uchar fun1(uchar code)
{
	uchar f1 = 0;
	int count = 7;//记录移位次数

	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0, xy1 = 0;//两位中的低位0与高位1
		xy1 = code&(1 << count);//从高位开始，两位两位比较
		xy = code&(1 << count - 1);
		f1 |= (xy || xy1) << 3 - i;//从高位开始保存
		count -= 2;

	}
	return f1;
}
//fun2 与     fun1 或
uchar fun2(uchar code)
{
	uchar f2 = 0;
	int count = 7;//记录移位次数
	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0, xy1 = 0;//
		xy1 = code&(1 << count);
		xy = code&(1 << count - 1);
		f2 |= (xy && xy1) << 3 - i;//
		count -= 2;
	}
	return f2;

}
//fun3 或非 只需要对或取非
uchar fun3(uchar code)
{
	code = fun1(code);
	uchar f1 = 0;
	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0;//一位
		xy = ((code&(1 << 3 - i)) == 0);

		f1 |= xy << 3 - i;//

	}
	return f1;
}
//fun4 与非
uchar fun4(uchar code)
{
	code = fun2(code);
	uchar f1 = 0;
	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0;//一位
		xy = ((code&(1 << 3 - i)) == 0);

		f1 |= xy << 3 - i;//
	}
	return f1;
}

///** funstr函数:  6位3个点
uchar funstr1(uchar code)
{
	uchar f1 = 0;
	int count = 7;//记录移位次数

	for (int i = 0; i < 6; i++)//i为移位数
	{
		uchar xy = 0, xy1 = 0, xy2 = 0;//3位中的低位0与高位1
		xy2 = code&(1 << count);//从高位开始，利用和1的并集移位取出该位数，进行两位两位比较
		xy1 = code&(1 << count - 1);
		xy = code&(1 << count - 2);
		f1 |= (xy || xy1 || xy2) << 5 - i;//从高位开始保存
		count -= 1;

	}
	return f1;
}
//fun2 与  和fun1计算方法一样，或变成与
uchar funstr2(uchar code)
{
	uchar f2 = 0;
	int count = 7;//记录移位次数
	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0, xy1 = 0, xy2 = 0;//
		xy2 = code&(1 << count);//从高位开始，利用和1的并集移位取出该位数，进行两位两位比较
		xy1 = code&(1 << count - 1);
		xy = code&(1 << count - 2);
		f2 |= (xy && xy1&&xy2) << 5 - i;//
		count -= 1;
	}
	return f2;

}
//fun3 或非 只需要对或取非
uchar funstr3(uchar code)
{
	code = funstr1(code);
	uchar f1 = 0;
	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0;//一位
		xy = ((code&(1 << 5 - i)) == 0);

		f1 |= xy << 5 - i;//

	}
	return f1;
}
//fun4 与非
uchar funstr4(uchar code)
{
	code = funstr2(code);
	uchar f1 = 0;
	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0;//一位
		xy = ((code&(1 << 5 - i)) == 0);

		f1 |= xy << 5 - i;//
	}
	return f1;
}

///逻辑矢量变换 **********************************************



///逻辑融合  *************************************************
//  或   4位
uchar funAC11(uchar cod, uchar cod1)
{
	uchar f1 = 0;
	int count = 3;//记录移位次数

	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0, xy1 = 0;//两位中的低位0与高位1
		xy1 = cod&(1 << count);//从高位开始，两位两位比较
		xy = cod1&(1 << count);
		f1 |= (xy || xy1) << 3 - i;//从高位开始保存
		count -= 1;

	}
	return f1;
}
//  与   4位
uchar funAC12(uchar cod, uchar cod1)
{
	uchar f1 = 0;
	int count = 3;//记录移位次数

	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0, xy1 = 0;//两位中的低位0与高位1
		xy1 = cod&(1 << count);//从高位开始，两位两位比较
		xy = cod1&(1 << count);
		f1 |= (xy && xy1) << 3 - i;//从高位开始保存
		count -= 1;

	}
	return f1;
}
//  或非 4位
uchar funAC13(uchar cod, uchar cod1)
{
	uchar cod0 = 0;
	cod0 = funAC11(cod, cod1);
	uchar f1 = 0;
	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0;//一位
		xy = ((cod0 & (1 << 3 - i)) == 0);

		f1 |= xy << 3 - i;//

	}
	return f1;
}
//  与非 4位
uchar funAC14(uchar cod, uchar cod1)
{
	uchar cod0 = 0;
	cod0 = funAC12(cod, cod1);
	uchar f1 = 0;
	for (int i = 0; i < 4; i++)
	{
		uchar xy = 0;//一位
		xy = ((cod0 & (1 << 3 - i)) == 0);

		f1 |= xy << 3 - i;//

	}
	return f1;
}

//  或   6位
uchar funAC21(uchar cod, uchar cod1)
{
	uchar f1 = 0;
	int count = 5;//记录移位次数

	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0, xy1 = 0;//两位中的低位0与高位1
		xy1 = cod&(1 << count);//从高位开始，两位两位比较
		xy = cod1&(1 << count);
		f1 |= (xy || xy1) << 5 - i;//从高位开始保存
		count -= 1;

	}
	return f1;
}
//  与   6位
uchar funAC22(uchar cod, uchar cod1)
{
	uchar f1 = 0;
	int count = 5;//记录移位次数

	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0, xy1 = 0;//两位中的低位0与高位1
		xy1 = cod&(1 << count);//从高位开始，两位两位比较
		xy = cod1&(1 << count);
		f1 |= (xy && xy1) << 5 - i;//从高位开始保存
		count -= 1;

	}
	return f1;
}
//  或非 6位
uchar funAC23(uchar cod, uchar cod1)
{
	uchar cod0 = 0;
	cod0 = funAC21(cod, cod1);
	uchar f1 = 0;
	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0;//一位
		xy = ((cod0 & (1 << 5 - i)) == 0);

		f1 |= xy << 5 - i;//

	}
	return f1;
}
//  与非 6位
uchar funAC24(uchar cod, uchar cod1)
{
	uchar cod0 = 0;
	cod0 = funAC22(cod, cod1);
	uchar f1 = 0;
	for (int i = 0; i < 6; i++)
	{
		uchar xy = 0;//一位
		xy = ((cod0 & (1 << 5 - i)) == 0);

		f1 |= xy << 5 - i;//

	}
	return f1;
}

///矢量融合  *************************************************



///LLVP的各个特征*********************************************
//LLVP_C第一条线段   fun 1,2,3，4   4位 两位数
Mat LLVP_C1_fun(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i, j - 4) >= center) << 7;
			code |= (img.at<uchar>(i, j - 3) >= center) << 6;
			code |= (img.at<uchar>(i, j - 2) >= center) << 5;
			code |= (img.at<uchar>(i, j - 1) >= center) << 4;
			code |= (img.at<uchar>(i, j + 1) >= center) << 3;
			code |= (img.at<uchar>(i, j + 2) >= center) << 2;
			code |= (img.at<uchar>(i, j + 3) >= center) << 1;
			code |= (img.at<uchar>(i, j + 4) >= center) << 0;
			if (funtype == 1)
			{
				code1 = fun1(code);
			}
			if (funtype == 2)
			{
				code1 = fun2(code);
			}
			if (funtype == 3)
			{
				code1 = fun3(code);
			}
			if (funtype == 4)
			{
				code1 = fun4(code);
			}

			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_C第二条线段      
Mat LLVP_C2_fun(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i - 4, j) >= center) << 7;
			code |= (img.at<uchar>(i - 3, j) >= center) << 6;
			code |= (img.at<uchar>(i - 2, j) >= center) << 5;
			code |= (img.at<uchar>(i - 1, j) >= center) << 4;
			code |= (img.at<uchar>(i + 1, j) >= center) << 3;
			code |= (img.at<uchar>(i + 2, j) >= center) << 2;
			code |= (img.at<uchar>(i + 3, j) >= center) << 1;
			code |= (img.at<uchar>(i + 4, j) >= center) << 0;
			if (funtype == 1)
			{
				code1 = fun1(code);
			}
			if (funtype == 2)
			{
				code1 = fun2(code);
			}
			if (funtype == 3)
			{
				code1 = fun3(code);
			}
			if (funtype == 4)
			{
				code1 = fun4(code);
			}
			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_C两条线段合并		
void LLVPC_fun_next(int num, int num1, char pn, int c, int funtype)//num-起始样本，num1-结束样本， pn-区分正负样本，
{
	char filename[250];
	ofstream  outfile;
	//文件路径
	if (num == 1)
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPC\\extract\\%dfunLLVPC_%d%c.txt", funtype, num1, pn);//8000p.txt  8000n.txt 保存文件
	}
	else
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPC\\extract\\%dfunLLVPC_%d%c.txt", funtype, num1 - num + 1, pn);//2000p.txt 2000n.txt
	}

	outfile.open(filename);//样本文件

	for (int i = num; i <= num1; i++)
	{
		char 	imgfile[250];//样本地址


		Mat_<double> Q(1, 672);
		Mat_<double> Q1(1, 336);
		Mat_<double> Q2(1, 336);

		int d = 0;
		int weishu = 0;
		//得到lbp特征Mat
		if (c == 1)
		{

			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\pos\\%d.bmp", i);//正样本地址

		}
		else
		{
			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\neg\\%d.bmp", i);//负样本地址

		}
		Mat src = imread(imgfile, 0);//gray image
		Mat dst;
		Mat dst1;
		copyMakeBorder(src, dst, 6, 6, 6, 6, BORDER_REFLECT);
		Mat result;
		blur(dst, result, Size(5, 5));//均值滤波
		Mat img;
		Mat img2;

		//先算出来特征
		switch (funtype)
		{

		case 1:		 img = LLVP_C1_fun(result, 1);
			img2 = LLVP_C2_fun(result, 1);
			break;
		case 2:		 			img = LLVP_C1_fun(result, 2);
			img2 = LLVP_C2_fun(result, 2);
			break;
		case 3:		 			img = LLVP_C1_fun(result, 3);
			img2 = LLVP_C2_fun(result, 3);
			break;
		case 4:		 			img = LLVP_C1_fun(result, 4);
			img2 = LLVP_C2_fun(result, 4);

			break;
		}


		//namedWindow("ok");
		//imshow("ok", img);
		//waitKey(0);

		//金字塔分割
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 15; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 16; q++)  //归一化并存储
						{
							Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 16;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			 //cout <<ab<<" ";
										for (int p = 0; p <= 15; p++)//59类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 15; q++)  //归一化并存储
								{
									Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 16;
							}//n
						}//m
					}
				}

		}//piece
		normalize(Q1, Q1, 1.0, 0.0, NORM_MINMAX);

		d = 0;
		weishu = 0;
		//金字塔分割 另外的funsd
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 15; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 16; q++)  //归一化并存储
						{
							Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 16;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			  //cout <<ab<<" ";
										for (int p = 0; p <= 15; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 15; q++)  //归一化并存储
								{
									Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 15;
							}//n
						}//m
					}
				}

		}//piece

		normalize(Q2, Q2, 1.0, 0.0, NORM_MINMAX);

		for (int i = 0; i<336; i++)
		{
			Q(0, i) = Q1(0, i);
		}

		for (int i = 0; i<336; i++)
		{
			Q(0, i + 336) = Q2(0, i);
		}


		for (int i = 0; i<672; i++)
		{
			outfile << Q(0, i) << " ";
		}
		cout << "总维数" << 672 << "乘以" << i << endl;

	}// i
	outfile.close();
}

//LLVP_C第一条线段      funstr1,2,3，4   6位 两位数
Mat LLVP_C1_funstr1(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i, j - 4) >= center) << 7;
			code |= (img.at<uchar>(i, j - 3) >= center) << 6;
			code |= (img.at<uchar>(i, j - 2) >= center) << 5;
			code |= (img.at<uchar>(i, j - 1) >= center) << 4;
			code |= (img.at<uchar>(i, j + 1) >= center) << 3;
			code |= (img.at<uchar>(i, j + 2) >= center) << 2;
			code |= (img.at<uchar>(i, j + 3) >= center) << 1;
			code |= (img.at<uchar>(i, j + 4) >= center) << 0;
			if (funtype == 1)
			{
				code1 = funstr1(code);
			}
			if (funtype == 2)
			{
				code1 = funstr2(code);
			}
			if (funtype == 3)
			{
				code1 = funstr3(code);
			}
			if (funtype == 4)
			{
				code1 = funstr4(code);
			}

			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_C第二条线段      
Mat LLVP_C2_funstr1(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i - 4, j) >= center) << 7;
			code |= (img.at<uchar>(i - 3, j) >= center) << 6;
			code |= (img.at<uchar>(i - 2, j) >= center) << 5;
			code |= (img.at<uchar>(i - 1, j) >= center) << 4;
			code |= (img.at<uchar>(i + 1, j) >= center) << 3;
			code |= (img.at<uchar>(i + 2, j) >= center) << 2;
			code |= (img.at<uchar>(i + 3, j) >= center) << 1;
			code |= (img.at<uchar>(i + 4, j) >= center) << 0;
			if (funtype == 1)
			{
				code1 = funstr1(code);
			}
			if (funtype == 2)
			{
				code1 = funstr2(code);
			}
			if (funtype == 3)
			{
				code1 = funstr3(code);
			}
			if (funtype == 4)
			{
				code1 = funstr4(code);
			}
			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_C两条线段合并	
void LLVPC_funstr1_next(int num, int num1, char pn, int c, int funtype)//num-起始样本，num1-结束样本， pn-区分正负样本，
{
	char filename[250];
	ofstream  outfile;
	//文件路径
	if (num == 1)
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPC\\extract\\%dLLVPCstr_%d%c.txt", funtype, num1, pn);//8000p.txt  8000n.txt 保存文件
	}
	else
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPC\\extract\\%dLLVPCstr_%d%c.txt", funtype, num1 - num + 1, pn);//2000p.txt 2000n.txt
	}

	outfile.open(filename);//样本文件

	for (int i = num; i <= num1; i++)
	{
		char 	imgfile[250];//样本地址


		Mat_<double> Q(1, 2688);
		Mat_<double> Q1(1, 1344);
		Mat_<double> Q2(1, 1344);

		int d = 0;
		int weishu = 0;
		//得到lbp特征Mat
		if (c == 1)
		{

			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\pos\\%d.bmp", i);//正样本地址

		}
		else
		{
			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\neg\\%d.bmp", i);//负样本地址

		}
		Mat src = imread(imgfile, 0);//gray image
		Mat dst;
		Mat dst1;
		copyMakeBorder(src, dst, 6, 6, 6, 6, BORDER_REFLECT);
		Mat result;
		blur(dst, result, Size(5, 5));//均值滤波
		Mat img;
		Mat img2;

		//先算出来特征
		switch (funtype)
		{

		case 1:		 img = LLVP_C1_funstr1(result, 1);
			img2 = LLVP_C2_funstr1(result, 1);
			break;
		case 2:		 			img = LLVP_C1_funstr1(result, 2);
			img2 = LLVP_C2_funstr1(result, 2);
			break;
		case 3:		 			img = LLVP_C1_funstr1(result, 3);
			img2 = LLVP_C2_funstr1(result, 3);
			break;
		case 4:		 			img = LLVP_C1_funstr1(result, 4);
			img2 = LLVP_C2_funstr1(result, 4);

			break;
		}


		//namedWindow("ok");
		//imshow("ok", img);
		//waitKey(0);

		//金字塔分割
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 63; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 64; q++)  //归一化并存储
						{
							Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 64;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			 //cout <<ab<<" ";
										for (int p = 0; p <= 63; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 63; q++)  //归一化并存储
								{
									Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 64;
							}//n
						}//m
					}
				}

		}//piece
		normalize(Q1, Q1, 1.0, 0.0, NORM_MINMAX);

		d = 0;
		weishu = 0;
		//金字塔分割 另外的funsd
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 63; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 64; q++)  //归一化并存储
						{
							Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 64;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			  //cout <<ab<<" ";
										for (int p = 0; p <= 63; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 63; q++)  //归一化并存储
								{
									Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 64;
							}//n
						}//m
					}
				}

		}//piece

		normalize(Q2, Q2, 1.0, 0.0, NORM_MINMAX);

		for (int i = 0; i<1344; i++)
		{
			Q(0, i) = Q1(0, i);
		}

		for (int i = 0; i<1344; i++)
		{
			Q(0, i + 1344) = Q2(0, i);
		}


		for (int i = 0; i<2688; i++)
		{
			outfile << Q(0, i) << " ";
		}
		cout << "总维数" << 2688 << "乘以" << i << endl;

	}// i
	outfile.close();
}

//LLVP_A第一条线段      funsd1,2,3，4   4位 两位数
Mat LLVP_A1_fun(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i, j - 4) >= img.at<uchar>(i, j - 3)) << 7;
			code |= (img.at<uchar>(i, j - 3) >= img.at<uchar>(i, j - 2)) << 6;
			code |= (img.at<uchar>(i, j - 2) >= img.at<uchar>(i, j - 1)) << 5;
			code |= (img.at<uchar>(i, j - 1) >= img.at<uchar>(i, j)) << 4;
			code |= (img.at<uchar>(i, j) >= img.at<uchar>(i, j + 1)) << 3;
			code |= (img.at<uchar>(i, j + 1) >= img.at<uchar>(i, j + 2)) << 2;
			code |= (img.at<uchar>(i, j + 2) >= img.at<uchar>(i, j + 3)) << 1;
			code |= (img.at<uchar>(i, j + 3) >= img.at<uchar>(i, j + 3)) << 0;
			if (funtype == 1)
			{
				code1 = fun1(code);
			}
			if (funtype == 2)
			{
				code1 = fun2(code);
			}
			if (funtype == 3)
			{
				code1 = fun3(code);
			}
			if (funtype == 4)
			{
				code1 = fun4(code);
			}

			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_A第二条线段
Mat LLVP_A2_fun(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i - 4, j) >= img.at<uchar>(i - 3, j)) << 7;
			code |= (img.at<uchar>(i - 3, j) >= img.at<uchar>(i - 2, j)) << 6;
			code |= (img.at<uchar>(i - 2, j) >= img.at<uchar>(i - 1, j)) << 5;
			code |= (img.at<uchar>(i - 1, j) >= img.at<uchar>(i, j)) << 4;
			code |= (img.at<uchar>(i, j) >= img.at<uchar>(i + 1, j)) << 3;
			code |= (img.at<uchar>(i + 1, j) >= img.at<uchar>(i + 2, j)) << 2;
			code |= (img.at<uchar>(i + 2, j) >= img.at<uchar>(i + 3, j)) << 1;
			code |= (img.at<uchar>(i + 3, j) >= img.at<uchar>(i + 4, j)) << 0;
			if (funtype == 1)
			{
				code1 = fun1(code);
			}
			if (funtype == 2)
			{
				code1 = fun2(code);
			}
			if (funtype == 3)
			{
				code1 = fun3(code);
			}
			if (funtype == 4)
			{
				code1 = fun4(code);
			}

			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_A两条线段合并		
void LLVPA_fun_next(int num, int num1, char pn, int c, int funtype)//num-起始样本，num1-结束样本， pn-区分正负样本，
{
	char filename[250];
	ofstream  outfile;
	//文件路径
	if (num == 1)
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPA\\extract\\%dfunLLVPA_%d%c.txt", funtype, num1, pn);//8000p.txt  8000n.txt 保存文件
	}
	else
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPA\\extract\\%dfunLLVPA_%d%c.txt", funtype, num1 - num + 1, pn);//2000p.txt 2000n.txt
	}

	outfile.open(filename);//样本文件

	for (int i = num; i <= num1; i++)
	{
		char 	imgfile[250];//样本地址


		Mat_<double> Q(1, 672);
		Mat_<double> Q1(1, 336);
		Mat_<double> Q2(1, 336);

		int d = 0;
		int weishu = 0;
		//得到lbp特征Mat
		if (c == 1)
		{

			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\pos\\%d.bmp", i);//正样本地址

		}
		else
		{
			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\neg\\%d.bmp", i);//负样本地址

		}
		Mat src = imread(imgfile, 0);//gray image
		Mat dst;
		Mat dst1;
		copyMakeBorder(src, dst, 6, 6, 6, 6, BORDER_REFLECT);
		Mat result;
		blur(dst, result, Size(5, 5));//均值滤波
		Mat img;
		Mat img2;

		//先算出来特征
		switch (funtype)
		{

		case 1:		 img = LLVP_A1_fun(result, 1);
			img2 = LLVP_A2_fun(result, 1);
			break;
		case 2:		 			img = LLVP_A1_fun(result, 2);
			img2 = LLVP_A2_fun(result, 2);
			break;
		case 3:		 			img = LLVP_A1_fun(result, 3);
			img2 = LLVP_A2_fun(result, 3);
			break;
		case 4:		 			img = LLVP_A1_fun(result, 4);
			img2 = LLVP_A2_fun(result, 4);

			break;
		}


		//namedWindow("ok");
		//imshow("ok", img);
		//waitKey(0);

		//金字塔分割
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 15; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 16; q++)  //归一化并存储
						{
							Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 16;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			 //cout <<ab<<" ";
										for (int p = 0; p <= 15; p++)//59类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 15; q++)  //归一化并存储
								{
									Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 16;
							}//n
						}//m
					}
				}

		}//piece
		normalize(Q1, Q1, 1.0, 0.0, NORM_MINMAX);

		d = 0;
		weishu = 0;
		//金字塔分割 另外的funsd
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 15; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 16; q++)  //归一化并存储
						{
							Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 16;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			  //cout <<ab<<" ";
										for (int p = 0; p <= 15; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 15; q++)  //归一化并存储
								{
									Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 15;
							}//n
						}//m
					}
				}

		}//piece

		normalize(Q2, Q2, 1.0, 0.0, NORM_MINMAX);

		for (int i = 0; i<336; i++)
		{
			Q(0, i) = Q1(0, i);
		}

		for (int i = 0; i<336; i++)
		{
			Q(0, i + 336) = Q2(0, i);
		}


		for (int i = 0; i<672; i++)
		{
			outfile << Q(0, i) << " ";
		}
		cout << "总维数" << 672 << "乘以" << i << endl;

	}// i
	outfile.close();
}

//LLVP_A第一条线段      funstr1,2,3，4   6位 两位数
Mat LLVP_A1_funstr1(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i, j - 4) >= img.at<uchar>(i, j - 3)) << 7;
			code |= (img.at<uchar>(i, j - 3) >= img.at<uchar>(i, j - 2)) << 6;
			code |= (img.at<uchar>(i, j - 2) >= img.at<uchar>(i, j - 1)) << 5;
			code |= (img.at<uchar>(i, j - 1) >= img.at<uchar>(i, j)) << 4;
			code |= (img.at<uchar>(i, j) >= img.at<uchar>(i, j + 1)) << 3;
			code |= (img.at<uchar>(i, j + 1) >= img.at<uchar>(i, j + 2)) << 2;
			code |= (img.at<uchar>(i, j + 2) >= img.at<uchar>(i, j + 3)) << 1;
			code |= (img.at<uchar>(i, j + 3) >= img.at<uchar>(i, j + 3)) << 0;
			if (funtype == 1)
			{
				code1 = funstr1(code);
			}
			if (funtype == 2)
			{
				code1 = funstr2(code);
			}
			if (funtype == 3)
			{
				code1 = funstr3(code);
			}
			if (funtype == 4)
			{
				code1 = funstr4(code);
			}

			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_A第二条线段      
Mat LLVP_A2_funstr1(Mat img, int funtype)
{
	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   

	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			code |= (img.at<uchar>(i - 4, j) >= img.at<uchar>(i - 3, j)) << 7;
			code |= (img.at<uchar>(i - 3, j) >= img.at<uchar>(i - 2, j)) << 6;
			code |= (img.at<uchar>(i - 2, j) >= img.at<uchar>(i - 1, j)) << 5;
			code |= (img.at<uchar>(i - 1, j) >= img.at<uchar>(i, j)) << 4;
			code |= (img.at<uchar>(i, j) >= img.at<uchar>(i + 1, j)) << 3;
			code |= (img.at<uchar>(i + 1, j) >= img.at<uchar>(i + 2, j)) << 2;
			code |= (img.at<uchar>(i + 2, j) >= img.at<uchar>(i + 3, j)) << 1;
			code |= (img.at<uchar>(i + 3, j) >= img.at<uchar>(i + 4, j)) << 0;
			if (funtype == 1)
			{
				code1 = funstr1(code);
			}
			if (funtype == 2)
			{
				code1 = funstr2(code);
			}
			if (funtype == 3)
			{
				code1 = funstr3(code);
			}
			if (funtype == 4)
			{
				code1 = funstr4(code);
			}
			result.at<uchar>(i - 6, j - 6) = code1;
		}
	}
	return result;
}
//LLVP_A两条线段合并	
void LLVPA_funstr1_next(int num, int num1, char pn, int c, int funtype)//num-起始样本，num1-结束样本， pn-区分正负样本，
{
	char filename[250];
	ofstream  outfile;
	//文件路径
	if (num == 1)
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPA\\extract\\%dLLVPAstr_%d%c.txt", funtype, num1, pn);//8000p.txt  8000n.txt 保存文件
	}
	else
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPA\\extract\\%dLLVPAstr_%d%c.txt", funtype, num1 - num + 1, pn);//2000p.txt 2000n.txt
	}

	outfile.open(filename);//样本文件

	for (int i = num; i <= num1; i++)
	{
		char 	imgfile[250];//样本地址


		Mat_<double> Q(1, 2688);
		Mat_<double> Q1(1, 1344);
		Mat_<double> Q2(1, 1344);

		int d = 0;
		int weishu = 0;
		//得到lbp特征Mat
		if (c == 1)
		{

			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\pos\\%d.bmp", i);//正样本地址

		}
		else
		{
			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\neg\\%d.bmp", i);//负样本地址

		}
		Mat src = imread(imgfile, 0);//gray image
		Mat dst;
		Mat dst1;
		copyMakeBorder(src, dst, 6, 6, 6, 6, BORDER_REFLECT);
		Mat result;
		blur(dst, result, Size(5, 5));//均值滤波
		Mat img;
		Mat img2;

		//先算出来特征
		switch (funtype)
		{

		case 1:		 img = LLVP_A1_funstr1(result, 1);
			img2 = LLVP_A2_funstr1(result, 1);
			break;
		case 2:		 			img = LLVP_A1_funstr1(result, 2);
			img2 = LLVP_A2_funstr1(result, 2);
			break;
		case 3:		 			img = LLVP_A1_funstr1(result, 3);
			img2 = LLVP_A2_funstr1(result, 3);
			break;
		case 4:		 			img = LLVP_A1_funstr1(result, 4);
			img2 = LLVP_A2_funstr1(result, 4);

			break;
		}


		//namedWindow("ok");
		//imshow("ok", img);
		//waitKey(0);

		//金字塔分割
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 63; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 64; q++)  //归一化并存储
						{
							Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 64;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			 //cout <<ab<<" ";
										for (int p = 0; p <= 63; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 63; q++)  //归一化并存储
								{
									Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 64;
							}//n
						}//m
					}
				}

		}//piece
		normalize(Q1, Q1, 1.0, 0.0, NORM_MINMAX);

		d = 0;
		weishu = 0;
		//金字塔分割 另外的funsd
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 63; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 64; q++)  //归一化并存储
						{
							Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 64;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			  //cout <<ab<<" ";
										for (int p = 0; p <= 63; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 63; q++)  //归一化并存储
								{
									Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 64;
							}//n
						}//m
					}
				}

		}//piece

		normalize(Q2, Q2, 1.0, 0.0, NORM_MINMAX);

		for (int i = 0; i<1344; i++)
		{
			Q(0, i) = Q1(0, i);
		}

		for (int i = 0; i<1344; i++)
		{
			Q(0, i + 1344) = Q2(0, i);
		}


		for (int i = 0; i<2688; i++)
		{
			outfile << Q(0, i) << " ";
		}
		cout << "总维数" << 2688 << "乘以" << i << endl;

	}// i
	outfile.close();
}

//LLVP_AC第一条线段      funstr1,2,3，4   4位  fun融合 两位数
Mat LLVP_AC1_fun(Mat img, int funtype)
{


	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   
	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			uchar code2 = 0;
			uchar code3 = 0;
			uchar code4 = 0;
			code |= (img.at<uchar>(i, j - 4) >= center) << 7;
			code |= (img.at<uchar>(i, j - 3) >= center) << 6;
			code |= (img.at<uchar>(i, j - 2) >= center) << 5;
			code |= (img.at<uchar>(i, j - 1) >= center) << 4;
			code |= (img.at<uchar>(i, j + 1) >= center) << 3;
			code |= (img.at<uchar>(i, j + 2) >= center) << 2;
			code |= (img.at<uchar>(i, j + 3) >= center) << 1;
			code |= (img.at<uchar>(i, j + 4) >= center) << 0;

			code1 |= (img.at<uchar>(i, j - 4) >= img.at<uchar>(i, j - 3)) << 7;
			code1 |= (img.at<uchar>(i, j - 3) >= img.at<uchar>(i, j - 2)) << 6;
			code1 |= (img.at<uchar>(i, j - 2) >= img.at<uchar>(i, j - 1)) << 5;
			code1 |= (img.at<uchar>(i, j - 1) >= img.at<uchar>(i, j)) << 4;
			code1 |= (img.at<uchar>(i, j) >= img.at<uchar>(i, j + 1)) << 3;
			code1 |= (img.at<uchar>(i, j + 1) >= img.at<uchar>(i, j + 2)) << 2;
			code1 |= (img.at<uchar>(i, j + 2) >= img.at<uchar>(i, j + 3)) << 1;
			code1 |= (img.at<uchar>(i, j + 3) >= img.at<uchar>(i, j + 3)) << 0;
			code2 = fun1(code);
			code3 = fun2(code1);

			if (funtype == 1)
			{
				code4 = funAC21(code2, code3);
			}
			if (funtype == 2)
			{
				code4 = funAC22(code2, code3);
			}


			result.at<uchar>(i - 6, j - 6) = code4;
		}
	}
	return result;
}
//LLVP_AC第二条线段  
Mat LLVP_AC2_fun(Mat img, int funtype)
{


	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   
	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			uchar code2 = 0;
			uchar code3 = 0;
			uchar code4 = 0;
			code |= (img.at<uchar>(i - 4, j) >= center) << 7;
			code |= (img.at<uchar>(i - 3, j) >= center) << 6;
			code |= (img.at<uchar>(i - 2, j) >= center) << 5;
			code |= (img.at<uchar>(i - 1, j) >= center) << 4;
			code |= (img.at<uchar>(i + 1, j) >= center) << 3;
			code |= (img.at<uchar>(i + 2, j) >= center) << 2;
			code |= (img.at<uchar>(i + 3, j) >= center) << 1;
			code |= (img.at<uchar>(i + 4, j) >= center) << 0;

			code1 |= (img.at<uchar>(i - 4, j) >= img.at<uchar>(i - 3, j)) << 7;
			code1 |= (img.at<uchar>(i - 3, j) >= img.at<uchar>(i - 2, j)) << 6;
			code1 |= (img.at<uchar>(i - 2, j) >= img.at<uchar>(i - 1, j)) << 5;
			code1 |= (img.at<uchar>(i - 1, j) >= img.at<uchar>(i, j)) << 4;
			code1 |= (img.at<uchar>(i, j) >= img.at<uchar>(i + 1, j)) << 3;
			code1 |= (img.at<uchar>(i + 1, j) >= img.at<uchar>(i + 2, j)) << 2;
			code1 |= (img.at<uchar>(i + 2, j) >= img.at<uchar>(i + 3, j)) << 1;
			code1 |= (img.at<uchar>(i + 3, j) >= img.at<uchar>(i + 4, j)) << 0;

			code2 = fun1(code);
			code3 = fun2(code1);

			if (funtype == 1)
			{
				code4 = funAC21(code2, code3);

			}
			if (funtype == 2)
			{
				code4 = funAC22(code2, code3);

			}


			result.at<uchar>(i - 6, j - 6) = code4;
		}
	}
	return result;
}
//LLVP_AC两条线段合并
void LLVPAC_fun_next(int num, int num1, char pn, int c, int funtype)//num-起始样本，num1-结束样本， pn-区分正负样本，
{
	char filename[250];
	ofstream  outfile;
	//文件路径
	if (num == 1)
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPAC\\extract\\%dfunLLVPAC_%d%c.txt", funtype, num1, pn);//8000p.txt  8000n.txt 保存文件
	}
	else
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPAC\\extract\\%dfunLLVPAC_%d%c.txt", funtype, num1 - num + 1, pn);//2000p.txt 2000n.txt
	}

	outfile.open(filename);//样本文件

	for (int i = num; i <= num1; i++)
	{
		char 	imgfile[250];//样本地址


		Mat_<double> Q(1, 672);
		Mat_<double> Q1(1, 336);
		Mat_<double> Q2(1, 336);

		int d = 0;
		int weishu = 0;
		//得到lbp特征Mat
		if (c == 1)
		{

			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\pos\\%d.bmp", i);//正样本地址

		}
		else
		{
			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\neg\\%d.bmp", i);//负样本地址

		}
		Mat src = imread(imgfile, 0);//gray image
		Mat dst;
		Mat dst1;
		copyMakeBorder(src, dst, 6, 6, 6, 6, BORDER_REFLECT);
		Mat result;
		blur(dst, result, Size(5, 5));//均值滤波
		Mat img;
		Mat img2;

		//先算出来特征
		switch (funtype)
		{

		case 1:		 img = LLVP_AC1_fun(result, 1);
			img2 = LLVP_AC2_fun(result, 1);
			break;
		case 2:		 			img = LLVP_AC1_fun(result, 2);
			img2 = LLVP_AC2_fun(result, 2);
			break;
		case 3:		 			img = LLVP_AC1_fun(result, 3);
			img2 = LLVP_AC2_fun(result, 3);
			break;
		case 4:		 			img = LLVP_AC1_fun(result, 4);
			img2 = LLVP_AC2_fun(result, 4);

			break;
		}


		//namedWindow("ok");
		//imshow("ok", img);
		//waitKey(0);

		//金字塔分割
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 15; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 16; q++)  //归一化并存储
						{
							Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 16;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			 //cout <<ab<<" ";
										for (int p = 0; p <= 15; p++)//59类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 15; q++)  //归一化并存储
								{
									Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 16;
							}//n
						}//m
					}
				}

		}//piece
		normalize(Q1, Q1, 1.0, 0.0, NORM_MINMAX);

		d = 0;
		weishu = 0;
		//金字塔分割 另外的funsd
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 15; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 16; q++)  //归一化并存储
						{
							Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 16;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[16] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			  //cout <<ab<<" ";
										for (int p = 0; p <= 15; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 15; q++)  //归一化并存储
								{
									Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 15;
							}//n
						}//m
					}
				}

		}//piece

		normalize(Q2, Q2, 1.0, 0.0, NORM_MINMAX);

		for (int i = 0; i<336; i++)
		{
			Q(0, i) = Q1(0, i);
		}

		for (int i = 0; i<336; i++)
		{
			Q(0, i + 336) = Q2(0, i);
		}


		for (int i = 0; i<672; i++)
		{
			outfile << Q(0, i) << " ";
		}
		cout << "总维数" << 672 << "乘以" << i << endl;

	}// i
	outfile.close();
}


//LLVP_AC第一条线段      funstr1,2,3，4   6位  fun融合 两位数
Mat LLVP_AC1_funstr1(Mat img, int funtype)
{


	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   
	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			uchar code2 = 0;
			uchar code3 = 0;
			uchar code4 = 0;
			code |= (img.at<uchar>(i, j - 4) >= center) << 7;
			code |= (img.at<uchar>(i, j - 3) >= center) << 6;
			code |= (img.at<uchar>(i, j - 2) >= center) << 5;
			code |= (img.at<uchar>(i, j - 1) >= center) << 4;
			code |= (img.at<uchar>(i, j + 1) >= center) << 3;
			code |= (img.at<uchar>(i, j + 2) >= center) << 2;
			code |= (img.at<uchar>(i, j + 3) >= center) << 1;
			code |= (img.at<uchar>(i, j + 4) >= center) << 0;

			code1 |= (img.at<uchar>(i, j - 4) >= img.at<uchar>(i, j - 3)) << 7;
			code1 |= (img.at<uchar>(i, j - 3) >= img.at<uchar>(i, j - 2)) << 6;
			code1 |= (img.at<uchar>(i, j - 2) >= img.at<uchar>(i, j - 1)) << 5;
			code1 |= (img.at<uchar>(i, j - 1) >= img.at<uchar>(i, j)) << 4;
			code1 |= (img.at<uchar>(i, j) >= img.at<uchar>(i, j + 1)) << 3;
			code1 |= (img.at<uchar>(i, j + 1) >= img.at<uchar>(i, j + 2)) << 2;
			code1 |= (img.at<uchar>(i, j + 2) >= img.at<uchar>(i, j + 3)) << 1;
			code1 |= (img.at<uchar>(i, j + 3) >= img.at<uchar>(i, j + 3)) << 0;

			if (funtype == 1)
			{
				code2 = funstr1(code);
				code3 = funstr2(code1);
			}
			if (funtype == 2)
			{
				code2 = funstr2(code);
				code3 = funstr1(code1);
			}
			if (funtype == 3)
			{
				code2 = funstr3(code);
				code3 = funstr3(code1);
			}
			if (funtype == 4)
			{
				code2 = funstr4(code);
				code3 = funstr4(code1);
			}

			code4 = funAC21(code2, code3);
			result.at<uchar>(i - 6, j - 6) = code4;
		}
	}
	return result;
}
//LLVP_AC第二条线段  
Mat LLVP_AC2_funstr1(Mat img, int funtype)
{


	Mat result;
	result.create(img.rows - 12, img.cols - 12, img.type());//48*48   
	result.setTo(0);

	for (int i = 6; i<img.rows - 6; i++)
	{
		for (int j = 6; j<img.cols - 6; j++)
		{
			uchar center = img.at<uchar>(i, j);
			uchar code = 0;
			uchar code1 = 0;
			uchar code2 = 0;
			uchar code3 = 0;
			uchar code4 = 0;
			code |= (img.at<uchar>(i - 4, j) >= center) << 7;
			code |= (img.at<uchar>(i - 3, j) >= center) << 6;
			code |= (img.at<uchar>(i - 2, j) >= center) << 5;
			code |= (img.at<uchar>(i - 1, j) >= center) << 4;
			code |= (img.at<uchar>(i + 1, j) >= center) << 3;
			code |= (img.at<uchar>(i + 2, j) >= center) << 2;
			code |= (img.at<uchar>(i + 3, j) >= center) << 1;
			code |= (img.at<uchar>(i + 4, j) >= center) << 0;

			code1 |= (img.at<uchar>(i - 4, j) >= img.at<uchar>(i - 3, j)) << 7;
			code1 |= (img.at<uchar>(i - 3, j) >= img.at<uchar>(i - 2, j)) << 6;
			code1 |= (img.at<uchar>(i - 2, j) >= img.at<uchar>(i - 1, j)) << 5;
			code1 |= (img.at<uchar>(i - 1, j) >= img.at<uchar>(i, j)) << 4;
			code1 |= (img.at<uchar>(i, j) >= img.at<uchar>(i + 1, j)) << 3;
			code1 |= (img.at<uchar>(i + 1, j) >= img.at<uchar>(i + 2, j)) << 2;
			code1 |= (img.at<uchar>(i + 2, j) >= img.at<uchar>(i + 3, j)) << 1;
			code1 |= (img.at<uchar>(i + 3, j) >= img.at<uchar>(i + 4, j)) << 0;

			if (funtype == 1)
			{
				code2 = funstr1(code);
				code3 = funstr1(code1);
			}
			if (funtype == 2)
			{
				code2 = funstr2(code);
				code3 = funstr1(code1);
			}
			if (funtype == 3)
			{
				code2 = funstr3(code);
				code3 = funstr3(code1);
			}
			if (funtype == 4)
			{
				code2 = funstr4(code);
				code3 = funstr4(code1);
			}


			code4 = funAC21(code2, code3);

			result.at<uchar>(i - 6, j - 6) = code4;
		}
	}
	return result;
}
//LLVP_AC两条线段合并
void LLVPAC_funstr1_next(int num, int num1, char pn, int c, int funtype)//num-起始样本，num1-结束样本， pn-区分正负样本，
{
	char filename[250];
	ofstream  outfile;
	//文件路径
	if (num == 1)
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPAC\\extract\\%dLLVPACstr_%d%c.txt", funtype, num1, pn);//8000p.txt  8000n.txt 保存文件
	}
	else
	{
		sprintf_s(filename, "E:\\Munich_photo_car\\LLVPAC\\extract\\%dLLVPACstr_%d%c.txt", funtype, num1 - num + 1, pn);//2000p.txt 2000n.txt
	}

	outfile.open(filename);//样本文件

	for (int i = num; i <= num1; i++)
	{
		char 	imgfile[250];//样本地址


		Mat_<double> Q(1, 2688);
		Mat_<double> Q1(1, 1344);
		Mat_<double> Q2(1, 1344);

		int d = 0;
		int weishu = 0;
		//得到lbp特征Mat
		if (c == 1)
		{

			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\pos\\%d.bmp", i);//正样本地址

		}
		else
		{
			sprintf_s(imgfile, "E:\\Munich_photo_car\\random_cutting\\neg\\%d.bmp", i);//负样本地址

		}
		Mat src = imread(imgfile, 0);//gray image
		Mat dst;
		Mat dst1;
		copyMakeBorder(src, dst, 6, 6, 6, 6, BORDER_REFLECT);
		Mat result;
		blur(dst, result, Size(5, 5));//均值滤波
		Mat img;
		Mat img2;

		//先算出来特征
		switch (funtype)
		{

		case 1:		 img = LLVP_AC1_funstr1(result, 1);
			img2 = LLVP_AC2_funstr1(result, 1);
			break;
		case 2:		 			img = LLVP_AC1_funstr1(result, 2);
			img2 = LLVP_AC2_funstr1(result, 2);
			break;
		case 3:		 			img = LLVP_AC1_funstr1(result, 3);
			img2 = LLVP_AC2_funstr1(result, 3);
			break;
		case 4:		 			img = LLVP_AC1_funstr1(result, 4);
			img2 = LLVP_AC2_funstr1(result, 4);

			break;
		}


		//namedWindow("ok");
		//imshow("ok", img);
		//waitKey(0);

		//金字塔分割
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 63; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 64; q++)  //归一化并存储
						{
							Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 64;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			 //cout <<ab<<" ";
										for (int p = 0; p <= 63; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 63; q++)  //归一化并存储
								{
									Q1(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 64;
							}//n
						}//m
					}
				}

		}//piece
		normalize(Q1, Q1, 1.0, 0.0, NORM_MINMAX);

		d = 0;
		weishu = 0;
		//金字塔分割 另外的funsd
		for (int piece = 1; piece <= 4; piece++) //前四种金字塔分割1*1,2*2,4*4
		{
			if (piece <= 2)
			{
				for (int m = 1; m < 49; m += 48 / piece)
				{
					for (int n = 1; n < 49; n += 48 / piece)
					{
						double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
											  //int sum = 0;
						for (int i = m; i < m + 48 / piece; i++)//进入小块
						{
							for (int j = n; j < n + 48 / piece; j++)
							{
								int ab = 0;

								ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab

								for (int p = 0; p <= 63; p++)//127类循环判定
								{
									if (ab == p)
									{
										a[p]++;//对应类个数加一
											   // sum++;
									}
								}
							}//j
						}//i

						 //	cout<<sum<<" ";
						for (int q = 0; q < 64; q++)  //归一化并存储
						{
							Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
							d++;
						}
						weishu += 64;
					}//n
				}//m
			}

			else
				if (piece == 4)
				{
					{
						for (int m = 1; m < 49; m += 48 / piece)
						{
							for (int n = 1; n < 49; n += 48 / piece)
							{
								double a[64] = { 0 }; //存储小样本块中每种LBP值的个数
													  //int sum = 0;
								for (int i = m; i < m + 48 / piece; i++)//进入小块
								{
									for (int j = n; j < n + 48 / piece; j++)
									{
										int ab = img2.at<uchar>(i - 1, j - 1);//将LBP值存到ab
																			  //cout <<ab<<" ";
										for (int p = 0; p <= 63; p++)//127类循环判定
										{
											if (ab == p)
											{
												a[p]++;
												//sum++;
											}
										}
									}//j
								}//i

								for (int q = 0; q <= 63; q++)  //归一化并存储
								{
									Q2(0, d) = a[q] / ((48 / piece)*(48 / piece));
									// cout<< a[q]<<" ";
									d++;
								}
								//cout<<sum<<" ";
								weishu += 64;
							}//n
						}//m
					}
				}

		}//piece

		normalize(Q2, Q2, 1.0, 0.0, NORM_MINMAX);

		for (int i = 0; i<1344; i++)
		{
			Q(0, i) = Q1(0, i);
		}

		for (int i = 0; i<1344; i++)
		{
			Q(0, i + 1344) = Q2(0, i);
		}


		for (int i = 0; i<2688; i++)
		{
			outfile << Q(0, i) << " ";
		}
		cout << "总维数" << 2688 << "乘以" << i << endl;

	}// i
	outfile.close();
}

///LLVP的各个特征*********************************************



int main()
{
	//	LLVPA_fun_next(1, 4000, 'p', 1, 2);
	//	LLVPA_fun_next(4001, 5000, 'p', 1, 2);
	//	LLVPA_fun_next(1, 4000, 'n', 0, 2);
	//	LLVPA_fun_next(4001, 5000, 'n', 0, 2);

	//	LLVPAC_funstr1_next(1, 4000, 'p', 1, 2);
	//	LLVPAC_funstr1_next(4001, 5000, 'p', 1, 2);
	//	LLVPAC_funstr1_next(1, 4000, 'n', 0, 2);
	//	LLVPAC_funstr1_next(4001, 5000, 'n', 0, 2);

	//	LLVPAC_fun_next(1, 4000, 'p', 1, 2);
	//	LLVPAC_fun_next(4001, 5000, 'p', 1, 2);
	//	LLVPAC_fun_next(1, 4000, 'n', 0, 2);
	//	LLVPAC_fun_next(4001, 5000, 'n', 0, 2);


	//  LLVPC_fun_next(1, 4000, 'p', 1, 1);
	//  LLVPC_fun_next(4001, 5000, 'p', 1, 1);
	//  LLVPC_fun_next(1, 4000, 'n', 0, 1);
	//  LLVPC_fun_next(4001, 5000, 'n', 0, 1);

}
