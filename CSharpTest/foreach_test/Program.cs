using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


// ysoftman
// foreach 가 for 비해서 일반적으로 느리지만 2차원 배열등의 순환시 루프 중첩을 피할 수 있다.
namespace foreach_test
{
	class Program
	{
		static void Main(string[] args)
		{
			// 1차원 배열에 대해서
			int[] arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			Console.WriteLine("arr.Rank:{0}", arr.Rank);
			Console.WriteLine("arr.Length:{0}", arr.Length);
			int sum = 0;
			for (int i = 0; i < arr.Length; i++)
			{
				sum += arr[i];
			}
			Console.WriteLine("(for) arr sum = {0}", sum);

			sum = 0;
			foreach (int i in arr)
			{
				sum += i;
			}
			Console.WriteLine("(foreach) arr sum = {0}", sum);

			
			// 2차원 배열에 대해서
			int[,] arr2 = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 9, 10 } };
			Console.WriteLine("arr2.Rank:{0}", arr2.Rank);

			// for 가 차원의 개수(rank) 만큼 중첩하여 원소에 접근해야 한다.
			sum = 0;
			for (int i = 0; i < arr2.GetLength(0); i++)
			{
				for (int j = 0; j < arr2.GetLength(1); j++)
				{
					Console.WriteLine("arr2[{0}, {1}] = {2}", i, j, arr2[i, j]);
					sum += arr2[i, j];
				}
			}
			Console.WriteLine("(for) arr2 sum = {0}", sum);

			
			// foreach 로 루프의 중첩없이 각 원소에 쉽게 접근할 수 있다.
			sum = 0;
			foreach (int i in arr2)
			{
				Console.WriteLine(i);
				sum += i;
			}
			Console.WriteLine("(foreach) arr2 sum = {0}", sum);
		}
	}
}
