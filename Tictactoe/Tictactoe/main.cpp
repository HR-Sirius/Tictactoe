#include<graphics.h>
#include<iostream>

//����������Ϊȫ�ֶ�ά����
char Board_data[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'}
};

//������ǰ��������
char current_chesstype = 'O';

//���ָ�����ӵ�����Ƿ��ʤ
bool CheckWin(char c)
{
	//��������
	if (Board_data[0][0] == c && Board_data[0][1] == c && Board_data[0][2] == c)
		return true;
	if (Board_data[1][0] == c && Board_data[1][1] == c && Board_data[1][2] == c)
		return true;
	if (Board_data[2][0] == c && Board_data[2][1] == c && Board_data[2][2] == c)
		return true;
	//��������
	if (Board_data[0][0] == c && Board_data[1][0] == c && Board_data[2][0] == c)
		return true;
	if (Board_data[0][1] == c && Board_data[1][1] == c && Board_data[2][1] == c)
		return true;
	if (Board_data[0][2] == c && Board_data[1][2] == c && Board_data[2][2] == c)
		return true;
	//�Խ�������
	if (Board_data[0][0] == c && Board_data[1][1] == c && Board_data[2][2] == c)
		return true;
	if (Board_data[0][2] == c && Board_data[1][1] == c && Board_data[2][0] == c)
		return true;

	return false;
}

//��⵱ǰ��Ϸ�Ƿ�ƽ��
bool CheckDraw()
{
	//����������ÿһ��Ԫ�أ���Ϊ'-'��˵��δƽ��
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (Board_data[i][j] == '-')
				return false;
		}

	return true;
}

//������������
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//��������
void DrawChess()
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			//�˴�ע���ά���鰴�д洢�����Ҫ������
			switch (Board_data[i][j])
			{
			case 'O':circle(j * 200 + 100, i * 200 + 100, 100); break;
			case 'X':line(j * 200, i * 200, j * 200 + 200, i * 200 + 200); line(j * 200 + 200, i * 200, j * 200, i * 200 + 200); break;
			case '-':break;
			}
		}
}

//������ʾ��Ϣ
void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ��������:%c"), current_chesstype);

	//�����ı���ɫ
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}


int main()
{
	initgraph(600, 600);

	//�жϵ�ǰ��Ϸ�Ƿ����
	bool flag = true;

	ExMessage msg;

	BeginBatchDraw();

	//��Ϸ��ѭ��
	while (flag)
	{
		//��ȡ��Ϣ
		while (peekmessage(&msg))
		{
			//���������������Ϣ
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				//���������λ���ڶ�ά�����е�ӳ��
				int index_x = x / 200;
				int index_y = y / 200;

				//��������������
				if (Board_data[index_y][index_x] == '-')
				{
					Board_data[index_y][index_x] = current_chesstype;

					//�޸���������
					if (current_chesstype == 'O')
					{
						current_chesstype = 'X';
					}
					else
					{
						current_chesstype = 'O';
					}
				}
			}
		}

		cleardevice();

		DrawBoard();
		DrawChess();
		DrawTipText();

		FlushBatchDraw();

		//��Ϣ����
		if (CheckWin('X'))
		{
			MessageBox(GetHWnd(), _T("X��һ�ʤ!"), _T("��Ϸ����"), MB_OK);
			flag = false;
		}
		else if (CheckWin('O'))
		{
			MessageBox(GetHWnd(), _T("O��һ�ʤ!"), _T("��Ϸ����"), MB_OK);
			flag = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("ƽ��!"), _T("��Ϸ����"), MB_OK);
			flag = false;
		}
	}

	EndBatchDraw();
	return 0;
}