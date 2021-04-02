#include <iostream>
#include <climits>
#include <vector>
using namespace std;

/*
int get_change(int m) {
	int n = 0;
	int change = 10;
	while(m != 0)
	{
		while(m >= change)
		{
			m -= change;
			n++;
		}
		if(change == 10)
			change = 5;
		else if(change == 5)
		{
			change = 1;
			n += m;// m = 3, so 3 = 1+1+1, i.e nothing but n+=m
			m =0;
		}
	}
	return n;
}*/

int get_change_dp(int money)
{
	vector<int> minNoOfcoins(money+1);//****************
	minNoOfcoins[0] = 0;
	vector<int> coins = {1, 3, 4};
	
	for(int i = 1; i <= money; ++i)
	{
		minNoOfcoins[i] = INT_MAX;
		for(size_t j = 0; j < coins.size(); ++j)
		{
			if(coins[j] <= i)
			{
				int NoOfCoins = minNoOfcoins[i - coins[j]] + 1;//+1 here we give one coins(1/3/4), and that i-coin value(1/3/4)
				if(NoOfCoins <  minNoOfcoins[i])//so for 3(money/i) with 1 coin, giving +1(1coin) and then 3-1 = 2, so i should find minNoOfcoins required to give me 2 as change, this is already there in the table as we doing dp from 1 to money
					minNoOfcoins[i] = NoOfCoins;//so for 3(money/i) with 3 coin, giving +1(3coin) and then 3-3 = 0, so i should find minNoofcoins required to give 0 as change, that is there in the tabel """"
			}//so for all money i.e from 1 to money, we calculate NoOFcoins with all 3 coins and place the min of that in minNoOFcoins[i];
		}
	}
	return minNoOfcoins[money];
}

int main() {
	int m;
	cin >> m;
	//cout << get_change(m) << '\n';
	cout << get_change_dp(m) << '\n';
}
