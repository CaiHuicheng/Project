class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result;
        int size1 = nums1.size();
        int size2 = nums2.size();
        for( int i = 0;i <= size1;i++ )//从第一个数组中取 i 个元素
        {
            if( i > k ) break;//最多取 k 个
            if(  size2 >= k -i )//第二个数组中能取够剩余元素
            {
                vector<int> vec1 = getMax(nums1,i);
                vector<int> vec2 = getMax(nums2,k-i);
                vector<int> res = meger2vec(vec1,vec2);
                result = max(result,res);
            }
        }
        return result;
    }
    //从数组中取 k 位数字，并保持相对顺序，使其构成的数字最大
    vector<int> getMax(vector<int>& nums1,int k)
    {
        //要使数字最大，就使从左到右每一位尽可能的最大，即单调递减

        vector<int> result;//返回结果
        int size = nums1.size();
        int remain = size -k;//允许丢弃的元素个数
        for( auto &num : nums1)
        {
            //如果下个元素值比当前位置的值大，则可以选择舍弃当前元素
            //但可舍弃的元素个数小于 1 时，表示不能再舍弃元素了，只能添加
            while( result.size() > 0 && remain > 0 && num > result.back() )
            {
                remain--;//允许舍弃的元素个数减一
                result.pop_back();//末尾删除元素
            }
            if( result.size() < k ) //未取够k个，添加到末尾
            {
                result.push_back(num) ;
            }
            else//已经取够了k个，直接丢弃
            {
                remain--;
            }    
        }
        return result;
    }
    //合并两个递减数组,使结果保存递减,并且构成的数字最大
     vector<int> meger2vec(vector<int>& nums1,vector<int>& nums2)
     {
         //当两个位置数值一样时，要接着比较下一位，以使下一位尽可能的大
         vector<int> result;
         int size1 = nums1.size();
         int size2 = nums2.size();
         int i = 0;
         int j = 0;
         while( i < size1 && j < size2)
         {
             //哪个大取哪个，当前位置相同就继续比较下一位
             //if( vector<int>(nums1.begin()+i,nums1.end()) > vector<int>(nums2.begin()+j,nums2.end()) )
             if( !lexicographical_compare(nums1.begin()+i,nums1.end(),nums2.begin()+j,nums2.end()) )
             {
                 result.push_back(nums1[i]);
                 i++;
             }
             else
             {
                 result.push_back(nums2[j]);
                 j++;
             }
         }
         //拷贝剩余元素到结果数组
         copy(nums1.begin()+i,nums1.end(),back_inserter(result));
         copy(nums2.begin()+j,nums2.end(),back_inserter(result));
         return result;
     }
};