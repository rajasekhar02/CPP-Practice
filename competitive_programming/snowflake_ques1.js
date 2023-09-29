

let max_cons_vowels = 2;
let stringLen = 2500;
let consV = 1e9+7;

let possibleWays = function(wordLen, consecutive_vowels){
    if(wordLen == 0){
        return 1;
    }
    if(consecutive_vowels == 0){
        return (21*possibleWays(wordLen-1, max_cons_vowels))%consV;
    }
    if(dp[wordLen][consecutive_vowels] != -1){
        return dp[wordLen][consecutive_vowels];
    }
    const withVowels = (5*possibleWays(wordLen-1,consecutive_vowels-1))%consV;
    const withoutVowels = (21*possibleWays(wordLen-1,max_cons_vowels))%consV;
    dp[wordLen][consecutive_vowels] = (withoutVowels+withVowels)%consV
    return dp[wordLen][consecutive_vowels];
}
let dp = new Array(stringLen+1).fill(1).map(x=> new Array(max_cons_vowels+1).fill(-1));
possibleWays(stringLen,max_cons_vowels)
