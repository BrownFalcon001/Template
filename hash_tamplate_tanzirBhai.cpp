/*
  Call init() before doing anything for gob's sake.
  Change query return type to ll or pii depending on number of hashes.
  Vector is really slow.
  String ->abcde, base 10, a is 1
  hash array will be-> [1, 12, 123, 1234, 12345]
  hash value will be ->12345
  query(2,3)->34
  update will only work for hash value. Array will not be modified and will be inconsistent.
  update(2, 'e') -> new hash value is 12545
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INFI 1e18
#define pii pair<ll, ll>
#define endl "\n"
#define N 2
#define MAX 10000

ll base[N], mod[N], power[N][MAX + 10];
ll totalHash;
void init()
{
  totalHash = 2;
  base[0] = 3407;
  base[1] = 4721;
  mod[0] = 1000003999;
  mod[1] = 1000000861;
  for (ll i = 0; i < totalHash; i++)
  {
    power[i][0] = 1;
    for (ll j = 1; j < MAX; j++)
    {
      power[i][j] = (power[i][j - 1] * base[i]) % mod[i];
    }
  }
}

struct HashData
{
  ll ara[N][MAX + 10], Hash[N];
  char str[MAX + 10];
  ll len;
  void init(char *s)
  {
    strcpy(str, s);
    len = strlen(str);
    for (ll i = 0; i < totalHash; i++)
    {
      ara[i][0] = str[0];
      for (ll j = 1; j < len; j++)
      {
        ara[i][j] = (ara[i][j - 1] * base[i]) % mod[i];
        ara[i][j] += str[j];
        if (ara[i][j] >= mod[i])
        {
          ara[i][j] -= mod[i];
        }
      }
      Hash[i] = ara[i][len - 1];
    }
  }

  inline pii query(ll st, ll ed)
  {
    ll ret[2];
    for (ll i = 0; i < totalHash; i++)
    {
      ll nw = ara[i][ed];
      if (st > 0)
      {
        nw -= (ara[i][st - 1] * power[i][ed - st + 1]) % mod[i];
        if (nw < 0)
        {
          nw += mod[i];
        }
        ret[i] = nw;
      }
      return {ret[0], ret[1]};
    }
  }

  inline void append(char c)
  {
    len++;
    for (ll i = 0; i < totalHash; i++)
    {
      if (len > 1)
      {
        ara[i][len - 1] = (ara[i][len - 2] * base[i]) % mod[i];
      }
      else
      {
        ara[i][len - 1] = 0;
      }
      ara[i][len - 1] += (c);
      if (ara[i][len - 1] >= mod[i])
      {
        ara[i][len - 1] -= mod[i];
      }
      Hash[i] = ara[i][len - 1];
    }
  }

  inline bool isEqual(const HashData &b)
  {
    for (ll i = 0; i < totalHash; i++)
    {
      if (Hash[i] != b.Hash[i])
        return false;
    }
    return true;
  }

  inline void Update(ll idx, char c)
  {
    for (ll i = 0; i < totalHash; i++)
    {
      Hash[i] -= (power[i][len - idx - 1] * str[idx]) % mod[i];
      if (Hash[i] < 0)
      {
        Hash[i] += mod[i];
      }
      Hash[i] += (power[i][len - idx - 1] * c) % mod[i];
      if (Hash[i] >= mod[i])
      {
        Hash[i] -= mod[i];
      }
    }
    str[idx] = c;
  }
  // void print()
  // {
  //   D(len);
  //   D(str);
  //   for (int i = 0; i < totalHash; i++)
  //   {
  //     puts("printing hash array");
  //     for (ll j = 0; j < len; j++)
  //     {
  //       cout << ara[i][j] << " ";
  //     }
  //     cout << endl;
  //     D(Hash[i]);
  //   }
  // }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  return 0;
}
