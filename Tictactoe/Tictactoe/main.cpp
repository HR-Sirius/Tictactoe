#include<graphics.h>
#include<iostream>

//将棋盘声明为全局二维数组
char Board_data[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'}
};

//标明当前落子类型
char current_chesstype = 'O';

//检测指定棋子的玩家是否获胜
bool CheckWin(char c)
{
	//横向三连
	if (Board_data[0][0] == c && Board_data[0][1] == c && Board_data[0][2] == c)
		return true;
	if (Board_data[1][0] == c && Board_data[1][1] == c && Board_data[1][2] == c)
		return true;
	if (Board_data[2][0] == c && Board_data[2][1] == c && Board_data[2][2] == c)
		return true;
	//纵向三连
	if (Board_data[0][0] == c && Board_data[1][0] == c && Board_data[2][0] == c)
		return true;
	if (Board_data[0][1] == c && Board_data[1][1] == c && Board_data[2][1] == c)
		return true;
	if (Board_data[0][2] == c && Board_data[1][2] == c && Board_data[2][2] == c)
		return true;
	//对角线三连
	if (Board_data[0][0] == c && Board_data[1][1] == c && Board_data[2][2] == c)
		return true;
	if (Board_data[0][2] == c && Board_data[1][1] == c && Board_data[2][0] == c)
		return true;

	return false;
}

//检测当前游戏是否平局
bool CheckDraw()
{
	//遍历棋盘中每一个元素，若为'-'则说明未平局
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (Board_data[i][j] == '-')
				return false;
		}

	return true;
}

//绘制棋盘网格
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//绘制棋子
void DrawChess()
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			//此处注意二维数组按行存储，因此要反过来
			switch (Board_data[i][j])
			{
			case 'O':circle(j * 200 + 100, i * 200 + 100, 100); break;
			case 'X':line(j * 200, i * 200, j * 200 + 200, i * 200 + 200); line(j * 200 + 200, i * 200, j * 200, i * 200 + 200); break;
			case '-':break;
			}
		}
}

//绘制提示信息
void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型:%c"), current_chesstype);

	//更改文本颜色
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}


int main()
{
	initgraph(600, 600);

	//判断当前游戏是否结束
	bool flag = true;

	ExMessage msg;

	BeginBatchDraw();

	//游戏主循环
	while (flag)
	{
		//获取消息
		while (peekmessage(&msg))
		{
			//检测鼠标左键按下消息
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				//计算鼠标点击位置在二维数组中的映射
				int index_x = x / 200;
				int index_y = y / 200;

				//按棋子类型落子
				if (Board_data[index_y][index_x] == '-')
				{
					Board_data[index_y][index_x] = current_chesstype;

					//修改棋子类型
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

		//消息处理
		if (CheckWin('X'))
		{
			MessageBox(GetHWnd(), _T("X玩家获胜!"), _T("游戏结束"), MB_OK);
			flag = false;
		}
		else if (CheckWin('O'))
		{
			MessageBox(GetHWnd(), _T("O玩家获胜!"), _T("游戏结束"), MB_OK);
			flag = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("平局!"), _T("游戏结束"), MB_OK);
			flag = false;
		}
	}

	EndBatchDraw();
	return 0;
}