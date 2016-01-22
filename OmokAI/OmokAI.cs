using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.IO;

/*
 * author	ysoftman
 * date		20121016
 * desc		오목 인공지능
 */
namespace OmokAI
{
	class OmokAI
	{
		public readonly static byte BRD_SIZE_X = 15;
		public readonly static byte BRD_SIZE_Y = BRD_SIZE_X;

		public readonly static byte DIA_BRD_SIZE_X = BRD_SIZE_X;
		public readonly static byte DIA_BRD_SIZE_Y = (byte)(BRD_SIZE_X * 2 - 1);

		public readonly static byte EMPTY = 0;
		public readonly static byte BLACK = 1;
		public readonly static byte WHITE = 2;
		public readonly static byte EDGE = 3;

		public readonly static int MIN_SCORE = -999;
		public readonly static int MAX_SCORE = 999;
		public readonly static int OMOK_SCORE = 100;

		public struct m_tPosition
		{
			public int x;
			public int y;
		}

		// 트리를 구성하는 하나의 노드
		public struct m_tNode
		{
			public m_tPosition pos;
			public int score;
			//public node parent = null;
			//public Dictionary<uint, node> child = new Dictionary<uint, node>();
			// 노드마다 보드를 가지고 있지 않고 전역 보드 하나만을 사용하도록 하여 메모리 사용량을 줄인다.
			//public int[,] board = new int[BRD_SIZE_Y, BRD_SIZE_X];
		}
		public static int m_Depth = 0;					// 탐색 깊이
		public static UInt64 m_EvalNodeCnt = 0;			// 평가된 노드의 개수
		public static uint m_Turn = 0;					// 현재 진행 수
		public Dictionary<uint, m_tPosition> m_Gibo = new Dictionary<uint, m_tPosition>();			// 기보 데이터
		
		public static int[,] m_Board = new int[BRD_SIZE_Y, BRD_SIZE_X];							// 현재까지 알이 놓인 상태의 판
		public static int[,] m_VerticalBoard = new int[BRD_SIZE_X, BRD_SIZE_Y];					// 수직 방향으로 스캔하여 만든 판
		public static int[,] m_LeftDiagonalBoard = new int[DIA_BRD_SIZE_Y, DIA_BRD_SIZE_X];		// 왼쪽 사선 방향으로 스캔하여 만든 판
		public static int[,] m_RightDiagonalBoard = new int[DIA_BRD_SIZE_Y, DIA_BRD_SIZE_X];		// 오른쪽 사선 방향의 수직 스캔하여 만든 판

		// 현재 진행된 판의 범위(사각형)
		public static int m_Left = 0;
		public static int m_Top = 0;
		public static int m_Right = 0;
		public static int m_Bottom = 0;

		public Dictionary<uint, int[]> m_PatternDB = new Dictionary<uint, int[]>();
		public Dictionary<uint, int> m_PatternScoreDB = new Dictionary<uint, int>();
		

		static void Main(string[] args)
		{
			Console.WriteLine("ysoftman OMOK AI");
			OmokAI obj = new OmokAI();
			obj.omok();
		}

		// 현재 기보 출력
		public void printbrdstatus(int[,] brd, int sizey, int sizex)
		{
			int x = 0;
			int y = 0;
			string str = "";
			Console.Write("   ");
			for (x = 0; x < sizex; x++)
			{
				if (x >= 10)
				{
					Console.Write("{0,1} ", x / 10);
				}
				else
				{
					Console.Write("{0,1} ", " ");
				}
			}
			Console.WriteLine("");

			Console.Write("   ");
			for (x = 0; x < sizex; x++)
			{
				Console.Write("{0,1} ", x % 10);
			}
			Console.WriteLine("");
			
			for (y = 0; y < sizey; y++)
			{
				Console.Write("{0,2} ", y);
				for (x = 0; x < sizex; x++)
				{
					if (brd[y, x] == 0)
					{
						str = ".";
					}
					else if (brd[y, x] == WHITE)
					{
						Console.ForegroundColor = ConsoleColor.Red;
						str = "O";
					}
					else if (brd[y, x] == BLACK)
					{
						Console.ForegroundColor = ConsoleColor.Green;
						str = "X";
					}
					Console.Write(str + " ");
					Console.ResetColor();
				}
				Console.WriteLine("");
			}
		}

		// 현재까지 진행된 판의 크기 범위 파악
		public void setrange()
		{
			int x = 0;
			int y = 0;
			bool find = false;

			for (x = 0; x < BRD_SIZE_X; x++)
			{
				for (y = 0; y < BRD_SIZE_Y; y++)
				{
					if (m_Board[y, x] != 0)
					{
						m_Left = x;
						find = true;
						break;
					}
				}
				if (find)
				{
					break;
				}
			}
			find = false;
			for (y = 0; y < BRD_SIZE_Y; y++)
			{
				for (x = 0; x < BRD_SIZE_X; x++)
				{
					if (m_Board[y, x] != 0)
					{
						m_Top = y;
						find = true;
						break;
					}
				}
				if (find)
				{
					break;
				}
			}
			find = false;
			for (x = BRD_SIZE_X - 1; x >= 0; x--)
			{
				for (y = 0; y < BRD_SIZE_Y; y++)
				{
					if (m_Board[y, x] != 0)
					{
						m_Right = x;
						find = true;
						break;
					}
				}
				if (find)
				{
					break;
				}
			}
			find = false;
			for (y = BRD_SIZE_Y - 1; y >= 0; y--)
			{
				for (x = 0; x < BRD_SIZE_X; x++)
				{
					if (m_Board[y, x] != 0)
					{
						m_Bottom = y;
						find = true;
						break;
					}
				}
				if (find)
				{
					break;
				}
			}
			//Console.WriteLine("current range m_Left = " + m_Left + " m_Right = " + m_Right + " m_Top = " + m_Top + " m_Bottom = " + m_Bottom);
		}

		public void omok()
		{
			Stopwatch sw = new Stopwatch();
			sw.Start();
			setpatternDB();
			Console.Clear();
			Console.CursorTop = 7;
			printbrdstatus(m_Board, BRD_SIZE_Y, BRD_SIZE_X);
			while (true)
			{
				m_Turn++;
				Console.CursorTop = 6;
				Console.WriteLine("Black(X) turn = {0,3}", m_Turn);
				m_Depth = 3;
				if (aiplay(BLACK) == false)
				//if (userplay(BLACK) == false)
				{
					Console.CursorTop = 30;
					Console.WriteLine("error!");
					break;
				}
				//Thread.Sleep(1000);
				Console.CursorTop = 7;
				printbrdstatus(m_Board, BRD_SIZE_Y, BRD_SIZE_X);
				calcscore(WHITE, true);
				if (calcscore(BLACK, true) == OMOK_SCORE)
				{
					Console.CursorTop = 30;
					Console.WriteLine("Black(X) Wins");
					break;
				}
				//Console.Write("\n\n");
				if (m_Turn >= BRD_SIZE_Y * BRD_SIZE_X)
				{
					break;
				}
				m_Turn++;
				Console.CursorTop = 6;
				Console.WriteLine("White(O) turn = {0,3}", m_Turn);
				m_Depth = 3;
				if (aiplay(WHITE) == false)
				//if (userplay(WHITE) == false)
				{
					Console.CursorTop = 30;
					Console.WriteLine("error!");
					break;
				}
				//Thread.Sleep(1000);
				Console.CursorTop = 7;
				printbrdstatus(m_Board, BRD_SIZE_Y, BRD_SIZE_X);
				calcscore(BLACK, true);
				if (calcscore(WHITE, true) == OMOK_SCORE)
				{
					Console.CursorTop = 30;
					Console.WriteLine("White(O) Wins");
					break;
				}
				//Console.Write("\n\n");
			}
			calcscore(BLACK, true);
			calcscore(WHITE, true);
			Console.CursorTop = 31;
			Console.WriteLine("total play(elapsed) time = {0,0}", sw.Elapsed.ToString());
			Array.Clear(m_Board, 0, m_Board.Length);
			m_Gibo.Clear();
			m_Turn = 0;
			Console.CursorTop = 32;
			Console.WriteLine("press 'Enter' key to play new game again.");
			Console.ReadLine();
			omok(); // 반복 테스트를 위해서 임시적용
		}

		// 사용자가 플레이
		public bool userplay(byte value)
		{
			m_tPosition pos;
			// 첫 수는 정중앙으로 한다.(오목 룰)
			if (m_Turn == 1)
			{
				pos.x = BRD_SIZE_X / 2;
				pos.y = BRD_SIZE_Y / 2;
				m_Board[pos.y, pos.x] = value;
				m_Gibo.Add(m_Turn, pos);
				Console.WriteLine("user chosen = {0,2},{1,2}", pos.y, pos.x);
				return true;
			}
			while (true)
			{
				try
				{
					//Random rand = new Random(System.DateTime.Now.Millisecond);
					//pos.x = rand.Next(BRD_SIZE_X);
					//pos.y = rand.Next(BRD_SIZE_Y);
					Console.CursorTop = 25;
					Console.CursorLeft = 0;
					Console.Write("input y = {0,50}", "");
					Console.CursorTop = 26;
					Console.CursorLeft = 0;
					Console.Write("input x = {0,50}", "");

					Console.CursorTop = 25;
					Console.CursorLeft = 0;
					Console.Write("input y = ");
					pos.y = int.Parse(Console.ReadLine());
					Console.CursorLeft = 0;
					Console.Write("input x = ");
					pos.x = int.Parse(Console.ReadLine());

					if (pos.y < BRD_SIZE_Y && pos.x < BRD_SIZE_X && m_Board[pos.y, pos.x] == 0)
					{
						m_Board[pos.y, pos.x] = (byte)value;
						m_Gibo.Add(m_Turn, pos);
						Console.WriteLine("user chosen = {0,2},{1,2}", pos.y, pos.x);
						return true;
					}
					Console.WriteLine("wrong position       ");
				}
				catch
				{
					Console.WriteLine("wrong position       ");
				}
			}
		}

		// 인공지능 플레이
		public bool aiplay(byte value)
		{
			m_tPosition pos;
			// 첫 수는 정중앙으로 한다.(오목 룰)
			if (m_Turn == 1)
			{
				pos.x = BRD_SIZE_X / 2;
				pos.y = BRD_SIZE_Y / 2;
				m_Board[pos.y, pos.x] = value;
				m_Gibo.Add(m_Turn, pos);
				Console.WriteLine("AI chosen = " + pos.y + "," + pos.x);
				return true;
			}
			// 2수까지는 바로 이전 수 주위로 한다.
			else if (m_Turn <= 2)
			{
				pos = m_Gibo[m_Turn-1];
				while (true)
				{
					//Random rand = new Random(System.DateTime.Now.Millisecond);
					//pos.x += rand.Next(2);
					//pos.y += rand.Next(2);
					// 테스트를 위해 고정된 좌표를 사용한다.
					pos.x += 1;
					pos.y += 1;
					if (pos.y < BRD_SIZE_Y && pos.x < BRD_SIZE_X && m_Board[pos.y, pos.x] == 0)
					{
						m_Board[pos.y, pos.x] = (byte)value;
						m_Gibo.Add(m_Turn, pos);
						Console.WriteLine("AI chosen = {0,2},{1,2}", pos.y, pos.x);
						return true;
					}
				}
			}
			Stopwatch sw = new Stopwatch();
			sw.Start();

			m_EvalNodeCnt = 0;

			m_tNode node;
			int alpha = MAX_SCORE;
			int beta = MIN_SCORE;
			node = makeminmaxtree(1, value, value, alpha, beta);
			if (node.pos.y == -1 || node.pos.x == -1)
			{
				return false;
			}
			m_Board[node.pos.y, node.pos.x] = value;

			Console.CursorTop = 1;
			Console.CursorLeft = 0;
			Console.WriteLine("total evaluted nodes = {0,7}", m_EvalNodeCnt);
			Console.CursorTop = 2;
			Console.CursorLeft = 0;
			Console.WriteLine("AI computation time = {0,0}", sw.Elapsed.ToString());
			Console.WriteLine("AI chosen = {0,2},{1,2}", node.pos.y, node.pos.x);

			m_Gibo.Add(m_Turn, node.pos);
			//GC.Collect();
			return true;
		}

		// 트리 구성 및 minmax 탐색하여 최선의 다음 위치(한수)를 파악한다.
		public m_tNode makeminmaxtree(int depth, byte aivalue, byte curvalue, int alpha, int beta)
		{
			m_tNode node = new m_tNode();
			node.pos.x = node.pos.y = -1;
			m_tNode childnode = new m_tNode();

			int x = 0;
			int y = 0;
			int fromx = 0;
			int tox = BRD_SIZE_X;
			int fromy = 0;
			int toy = BRD_SIZE_Y;

			// 현재 진행된 판의 크기를 파악해서 탐색 범위를 좁힌다.
			// 초반에 검은 돌과 횐돌이 멀리 떨어져 있으면 효과 없음
			//setrange();
			//fromx = m_Left - 3;
			//tox = m_Right + 3;
			//fromy = m_Top - 3;
			//toy = m_Bottom + 3;
			//if (fromx < 0) fromx = 0;
			//if (tox > BRD_SIZE_X) tox = BRD_SIZE_X;
			//if (fromy < 0) fromy = 0;
			//if (toy > BRD_SIZE_Y) toy = BRD_SIZE_Y;

			int score = 0;
			int min = MAX_SCORE;
			int max = MIN_SCORE;
			int i = 0;
			int j = 0;
			int aroundcnt = 0;
			for (y = fromy; y < toy; y++)
			{
				for (x = fromx; x < tox; x++)
				{
					if (m_Board[y, x] == 0)
					{
						// 현재 판에 알을 놓아 본다.
						m_Board[y, x] = curvalue;

						// 현재 놓인 알 주변에 알이 존재하지 않으면 더이상 탐색하지 않는다.
						aroundcnt = 0;
						for (j = y - 2; j <= y + 2; j++)
						{
							if (j < 0 || j >= toy)
							{
								continue;
							}
							for (i = x - 2; i <= x + 2; i++)
							{
								if (i < 0 || i >= tox)
								{
									continue;
								}
								if (m_Board[j, i] == BLACK || m_Board[j, i] == WHITE)
								{
									aroundcnt++;
								}
							}
						}
						if (aroundcnt <= 1)
						{
							m_Board[y, x] = 0;
							continue;
						}

						// 5목으로 끝나는 경우 체크를 위해 모든 노드에 대해서 평가한다.
						score = evaluate(aivalue);
						m_EvalNodeCnt++; // 평가된 노느의 개수 카운트


						// 노드 평가 진행중을 나타내기 위해서
						if (m_EvalNodeCnt % 1000 == 0)
						{
							Console.CursorLeft = 0;
							Console.CursorTop = 0;
							Console.BackgroundColor = ConsoleColor.Magenta;
							Console.ForegroundColor = ConsoleColor.Blue;
							Console.WriteLine("minmax tree depth = {0,2}  alpha = {1,4} beta = {2,4}  evaluted nodes = {3,7}", depth, alpha, beta, m_EvalNodeCnt);
							Console.ResetColor();
						}

						if (depth < m_Depth)
						{
							// 이길 수 밖에 없는 상황(점수)라면 하위 노드를 생성하지 않는다.
							if (score == OMOK_SCORE)
							{
								node.score = score;
								return node;
							}
							else
							{
								byte nextvalue = (curvalue == BLACK) ? WHITE : BLACK;
								childnode = makeminmaxtree(depth + 1, aivalue, nextvalue, alpha, beta);
								score = childnode.score;
							}
						}
						// 판에서 현재 노드가 놓은 알은 제거한다.(이전상태로 복구)
						m_Board[y, x] = 0;

						if (depth % 2 == 1)
						{
							if (max < score)
							{
								max = score;
								node.pos.x = x;
								node.pos.y = y;
								node.score = score;
								// alpha > beta 조건을 만족시키지 못하면 가지치기
								if (alpha > score)
								{
									beta = score;
								}
								else
								{
									// prunning
									return node;
								}
							}
						}
						else
						{
							if (min > score)
							{
								min = score;
								node.pos.x = x;
								node.pos.y = y;
								node.score = score;
								// alpha > beta 조건을 만족시키지 못하면 가지치기
								if (score > beta)
								{
									alpha = score;
								}
								else
								{
									// prunning
									return node;
								}
							}
						}
					}
				}
			}

			// 디버깅용
			if (node.pos.x == -1)
			{
				node.pos.x = -1;
			}
			return node;
		}

		// 평가
		public int evaluate(int aivalue)
		{
			int blackscore = calcscore(BLACK, false);
			int whitescore = calcscore(WHITE, false);

			if (aivalue == BLACK)
			{
				if (whitescore >= OMOK_SCORE)
				{
					return -whitescore;
				}
				if (blackscore >= OMOK_SCORE)
				{
					return blackscore;
				}
				return blackscore - whitescore;
			}
			else
			{
				if (blackscore >= OMOK_SCORE)
				{
					return -blackscore;
				}
				if (whitescore >= OMOK_SCORE)
				{
					return whitescore;
				}
				return whitescore - blackscore;
			}
		}

		// 돌의 점수 계산
		public int calcscore(byte value, bool printscore)
		{
			int x = 0;
			int y = 0;
			// 90 도 회전했을 때의 보드 만들기
			for (y = 0; y < BRD_SIZE_Y; y++)
			{
				for (x = 0; x < BRD_SIZE_X; x++)
				{
					// x, y 순서를 바꿔서 기록
					m_VerticalBoard[x, y] = m_Board[y, x];
				}
			}
			// 왼쪽 45 도 회전했을 때의 보드 만들기
			for (x = 0; x < DIA_BRD_SIZE_X; x++)
			{
				for (y = 0; y < DIA_BRD_SIZE_Y; y++)
				{
					m_LeftDiagonalBoard[y, x] = EDGE; // EDGE 값으로 초기화
				}
			}
			for (x = 0; x < BRD_SIZE_X; x++)
			{
				for (y = 0; y < BRD_SIZE_Y; y++)
				{
					if (x + y < BRD_SIZE_Y)
					{
						m_LeftDiagonalBoard[y + x, x] = m_Board[y, x];
					}
					else
					{
						m_LeftDiagonalBoard[y + x, (BRD_SIZE_Y - 1 - y)] = m_Board[y, x];
					}
				}
			}
			// 오른쪽 45 도 회전했을 때의 보드 만들기
			for (x = 0; x < DIA_BRD_SIZE_X; x++)
			{
				for (y = 0; y < DIA_BRD_SIZE_Y; y++)
				{
					m_RightDiagonalBoard[y, x] = EDGE; // EDGE 값으로 초기화
				}
			}
			for (x = 0; x < BRD_SIZE_X; x++)
			{
				for (y = 0; y < BRD_SIZE_Y; y++)
				{
					if (y <= x)
					{
						m_RightDiagonalBoard[(BRD_SIZE_X - 1 - (x - y)), y] = m_Board[y, x];
					}
					else
					{
						m_RightDiagonalBoard[(BRD_SIZE_X - 1 + (y - x)), x] = m_Board[y, x];
					}
				}
			}

			//Console.WriteLine("m_Board");
			//printbrdstatus(m_Board, BRD_SIZE_Y, BRD_SIZE_X);
			//Console.WriteLine("m_VerticalBoard");
			//printbrdstatus(m_VerticalBoard, BRD_SIZE_Y, BRD_SIZE_X);
			//Console.WriteLine("m_LeftDiagonalBoard");
			//printbrdstatus(m_LeftDiagonalBoard, DIA_BRD_SIZE_Y, DIA_BRD_SIZE_X);
			//Console.WriteLine("m_RightDiagonalBoard");
			//printbrdstatus(m_RightDiagonalBoard, DIA_BRD_SIZE_Y, DIA_BRD_SIZE_X);

			int score1 = 0;
			int score2 = 0;
			int score3 = 0;
			int score4 = 0;
			int resultscore = 0;

			score1 = checkpattern(m_Board, BRD_SIZE_X, BRD_SIZE_Y, value);
			score2 = checkpattern(m_VerticalBoard, BRD_SIZE_X, BRD_SIZE_Y, value);
			score3 = checkpattern(m_LeftDiagonalBoard, DIA_BRD_SIZE_X, DIA_BRD_SIZE_Y, value);
			score4 = checkpattern(m_RightDiagonalBoard, DIA_BRD_SIZE_X, DIA_BRD_SIZE_Y, value);
			//resultscore = score1 + score2 + score3 + score4;
			resultscore = Math.Max(score1, Math.Max(score2, Math.Max(score3, score4)));
			if (printscore)
			{
				Console.ForegroundColor = ConsoleColor.Yellow;
				string name = "";
				if (value == BLACK)
				{
					Console.CursorTop = 4;
					name = "Black(X)";
				}
				else
				{
					Console.CursorTop = 5;
					name = "White(O)";
				}
				Console.WriteLine("{0,0} score = Hor({1,3})  Ver({2,3})  LeftDia({3,3})  RightDia({4,3}) = Result({5,3})", name, score1, score2, score3, score4, resultscore);
				Console.ResetColor();
			}
			return resultscore;
		}


		int checkpattern(int[,] targetbrd, int targetbrdsizex, int targetbrdsizey, byte value)
		{
			int x = 0;
			int y = 0;
			int startx = 0;
			int endx = 0;
			int emptycnt = 0;
			int valuecnt = 0;
			int maxvaluecnt = 0;
			int findy = 0;
			int findstartx = 0;
			int findendx = 0;

			int maxpatterdbsize = m_PatternDB[0].GetLength(0);

			// 현재 판에서 연속된 돌이 가장 많은 지점을 파악한다.
			for (y = 0; y < targetbrdsizey; y++)
			{
				startx = endx = emptycnt = valuecnt = 0;
				for (x = 0; x < targetbrdsizex; x++)
				{
					if (targetbrd[y, x] == value)
					{
						if (valuecnt == 0)
						{
							startx = x;
						}
						endx = x;
						valuecnt++;
					}
					else if (targetbrd[y, x] == EMPTY && valuecnt > 0 && emptycnt < 2)
					{
						emptycnt++;
					}
					else
					{
						valuecnt = emptycnt = 0;
						continue;
					}
					// 6목이상의 패턴 제외
					if (maxpatterdbsize < valuecnt)
					{
						break;
					}
					if (valuecnt > maxvaluecnt)
					{
						maxvaluecnt = valuecnt;
						findstartx = startx;
						findendx = endx;
						findy = y;
					}
				}
			}
			// 파악된 지점만을 버퍼로 들고 있는다.
			int maxpatternsize = (findendx - findstartx) + 1;
			maxpatternsize += 2; // 앞뒤로 한개씩 더 넣기 위해서
			int[] maxpattern = new int[maxpatternsize];
			int i = 0;
			// 앞쪽에 한나 더 넣기
			if (findstartx == 0)
			{
				// 테두리선이라면 상대편 값으로
				maxpattern[i] = (value == BLACK) ? WHITE : BLACK;
			}
			else
			{
				// 대각선 보드일 경우 edge 로 표현되는 부분은 상대편 값으로
				if (targetbrd[findy, findstartx - 1] == EDGE)
				{
					maxpattern[i] = (value == BLACK) ? WHITE : BLACK;
				}
				else
				{
					maxpattern[i] = targetbrd[findy, findstartx - 1];
				}
			}
			i++;
			for (x = findstartx; x <= findendx; x++)
			{
				maxpattern[i] = targetbrd[findy, x];
				i++;
			}
			// 뒤쪽에 하나 더 넣기
			if (findendx == targetbrdsizex - 1)
			{
				// 테두리선이라면 상대편 값으로
				maxpattern[i] = (value == BLACK) ? WHITE : BLACK;
			}
			else
			{
				// 대각선 보드일 경우 edge 로 표현되는 부분은 상대편 값으로
				if (targetbrd[findy, findendx + 1] == EDGE)
				{
					maxpattern[i] = (value == BLACK) ? WHITE : BLACK;
				}
				else
				{
					maxpattern[i] = targetbrd[findy, findendx + 1];
				}
			}
			return matchpattern(maxpattern, value);
		}


		// 오목 패턴 리스트와 비교하여 점수 파악
		int matchpattern(int[] inputpattern, byte value)
		{
			int x = 0;
			byte matchcnt = 0;
			int patternsize = 0;
			int inputpatternsize = inputpattern.GetLength(0);
			uint i = 0;
			for (i = 0; i < m_PatternDB.Count; i++)
			{
				patternsize = m_PatternDB[i].GetLength(0);
				if (patternsize != inputpatternsize)
				{
					continue;
				}
				matchcnt = 0;
				for (x = 0; x < inputpatternsize; x++)
				{
					if (value == BLACK)
					{
						if ((m_PatternDB[i])[x] == 0 && inputpattern[x] == EMPTY)
						{
							matchcnt++;
						}
						else if ((m_PatternDB[i])[x] == 1 && inputpattern[x] == BLACK)
						{
							matchcnt++;
						}
						else if ((m_PatternDB[i])[x] == 2 && inputpattern[x] == WHITE)
						{
							matchcnt++;
						}
						else
						{
							break;
						}
					}
					else // value == WHITE
					{
						if ((m_PatternDB[i])[x] == 0 && inputpattern[x] == EMPTY)
						{
							matchcnt++;
						}
						else if ((m_PatternDB[i])[x] == 1 && inputpattern[x] == WHITE)
						{
							matchcnt++;
						}
						else if ((m_PatternDB[i])[x] == 2 && inputpattern[x] == BLACK)
						{
							matchcnt++;
						}
						else
						{
							break;
						}
					}
				}
				if (matchcnt == patternsize)
				{
					return m_PatternScoreDB[i];
				}
			}
			return 0;
		}

		// 패턴 구성하기
		public void setpatternDB()
		{
			// 0 = empty
			// 1 = mine (BLACK or WHITE)
			// 2 = opposite (BLACK or WHITE or edge)
			// 점수가 높은 순서대로 리스트를 구성한다.
			string filename = "../OmokAIPatternScore.txt";
			try
			{
				StreamReader sr = new StreamReader(filename, System.Text.Encoding.Default);
				string buffer = "";
				Console.WriteLine(filename + " reading");


				m_PatternDB.Clear();
				m_PatternScoreDB.Clear();
				uint index = 0;
				int i = 0;
				while ((buffer = sr.ReadLine()) != null)
				{
					// 엔터라인이나 주석라인은 건너뛰기
					if (buffer.Length == 0 || buffer[0] == '#')
					{
						continue;
					}
					// 스페이스 구분자
					string[] splitlist = buffer.Split(new char[] { ' ' });
					byte[] pattern = System.Text.Encoding.Default.GetBytes(splitlist[0]);
					int[] pattern2 = new int[pattern.GetLength(0)];
					for (i = 0; i < pattern.Length; i++)
					{
					    // ASCII 값으로 읽어 오니깨문에 0(48) 을 빼주어 정수로 기록
					    pattern2[i] = (byte)(pattern[i] - 48);
					}
					m_PatternDB.Add(index, pattern2);
					m_PatternScoreDB.Add(index, int.Parse(splitlist[1]));
					index++;
					Console.WriteLine(buffer);
				}
				sr.Close();
			}
			catch
			{
				Console.WriteLine("Can't read " + filename);
				System.Environment.Exit(0);
			}
		}
	}
}


