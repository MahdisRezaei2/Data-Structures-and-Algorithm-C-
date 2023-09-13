
#include <iostream>


// Recursive function to find the sum of number of paths
int numPathsFromHome( int street, int avenue){
    //  We have base cases here

        if (street ==0 || avenue ==0){
            return 1;
        }
        else{
            /**
             * if street or avenue is not equal to 0, we need to keep going
             * in fact, in this situation we are reaching to the base cases by decreasing the value of parameters
             * by addding the value of the 2 recursive calls of the function , we get the sum of the number of possible paths
             * we need to call the function once with deacresing the value of street and once calling the function with
             * decreasing the value of the avenue, because we are moving both vertically and horizontally
             * the addigng these two results together
            */
            return numPathsFromHome(street-1,avenue)+numPathsFromHome(street,avenue-1);
        }
    }



// The recursive function to ckeck subsequences
bool hasSubsequence(const char S[], const char T[], int indexInS, int indexInJ)
{
    // we have two base cases
    /**
     *  if length of S is less than T, we reach a point where have checked all the items in S, but not in T. in other words,
     * we have reached the end of S but not T. Example, 'Mah' and 'Mahdis'
     */
    if (S[indexInS] == '\0')
    {
        return true;
    }
    /**
     * Here, is the opoosite of previus condition, we reach end of the T, but not end of S yet, which is very possibaly
     * S is not subsequence of T, because for being subsequence we need the length of S be equal or less than length of T
     */
    else if (T[indexInJ] == '\0')
    {
        return false;
    }
    else if (S[indexInS] == T[indexInJ])
    {
        // if the items in these indicies are same, we need to check the rest of the array, so increment each index
        return hasSubsequence(S, T, indexInS + 1, indexInJ + 1);
    }
    else
    { /**
       * here, if we have an item in S that is not same as corresponding item in T, we keep traversing in T, to check if we
       *  can find the same item in T but in a different index , example 'hr' and 'here'
       */
        return hasSubsequence(S, T, indexInS, indexInJ + 1);
    }
}


/**
 * Here we have a helper function to call the recursive function hasSubsequence, this helper function helps us to call the recursive
 function with the indicies as parameter, which makes traversing in the array easier
*/

bool hasSubsequence(const char S[], const char T[])
{
    return hasSubsequence(S, T, 0, 0);
}



int main()
{    // Testing numPathFromHome function
    // Asking the user for position of the Eric's place
    std::cout<<"Enter the stree number of Eric's place "<<std::endl;
    std::cout<<"Enter the avenue number of Eric's place "<<std::endl;
    int street;
    int avenue; 
    std::cin>> street;
    std::cin>>avenue;
    // calling the function
    int numPath = numPathsFromHome(  street,  avenue);
    //showing the result
    std::cout<<"The number of possible paths is:  " << numPath<<std::endl;
    
     
    // Test cases for hasSubsequence function
    std::cout<<"Checking for subsequences :  "<<std::endl;
    std::cout << std::boolalpha << hasSubsequence("ping", "programming") << std::endl;
    std::cout << std::boolalpha << hasSubsequence("singe", "springtime") << std::endl;
    std::cout << std::boolalpha << hasSubsequence("steal", "least") << std::endl;
    // this test case is to make sure, that case sensitivity is working
    std::cout << std::boolalpha << hasSubsequence("agree", "AGREE") << std::endl;
    return 0;
}
