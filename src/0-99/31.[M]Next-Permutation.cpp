#include <stdio.h>
#include <string>
#include <vector>
#include "../include/all.h"
#include <functional>

using namespace std;

/***********************************************************
# 解题思路

* 采用递归分解的方法:
* 如果右边 n-1 个元素存在下一个排列, 则完成.
* 否则, 右边是倒序的. 让第 0 个元素与比它大的最小元素交换(如果有)并反转 n-1 个元素.
* 难点在于, 如果优化成二分查找, 那么要注意对中点公式的选取.
***********************************************************/
bool nextPermutationHelper(vector<int> &nums, int s){
	if(s >= nums.size() - 1){
		return false;
	}
	if(nextPermutationHelper(nums, s+1)){
		return true;
	}else{
		int f = nums[s];
		auto it = std::lower_bound(nums.begin()+s+1, nums.end(), f, greater<int>());
		int b = it - 1 - nums.begin();

		if(b == s){
			return false;
		}else{
			std::swap(nums[s], nums[b]);
			std::reverse(nums.begin() + s + 1, nums.end());
			return true;
		}
	}
}
void nextPermutation(vector<int>& nums) {
	if(!nextPermutationHelper(nums, 0)){
		std::reverse(nums.begin(), nums.begin() + nums.size());
	}
}

int main(int argc, char **argv){
	vector<int> nums = {1, 2, 3, 4};
	int count = 1;
	for(int i=2; i<=nums.size(); i++){
		count *= i;
	}
	count += 1;
	vector<int> n2 = nums;
	do{
		print_array(nums);
		std::next_permutation(n2.begin(), n2.end());
		nextPermutation(nums);
		if(n2 != nums){
			printf("error\n");
			break;
		}
	}while(--count > 0);
	
	nums = {1, 2, 3};
	nextPermutation(nums);
	print_array(nums);
	nums = {3, 2, 1};
	nextPermutation(nums);
	print_array(nums);
	nums = {1, 1, 5};
	nextPermutation(nums);
	print_array(nums);
	
	nums = {1, 1, 2,2};
	n2 = nums;
	for(int i=0; i<10; i++){
		print_array(nums);
		nextPermutation(nums);
		std::next_permutation(n2.begin(), n2.end());
		if(n2 != nums){
			printf("error\n");
			break;
		}
	}
	
	return 0;
}

/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/
