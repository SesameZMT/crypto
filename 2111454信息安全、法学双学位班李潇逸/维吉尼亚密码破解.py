import vigenerecipher

wf = [0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.02, 0.061, 0.07, 0.002, 0.008, 0.04, 0.024, 0.067, 0.075, 0.019, 0.001, 0.06, 0.063, 0.091, 0.028, 0.01, 0.023, 0.001, 0.02, 0.001]

def icm(cipher,key_len,cipher_len):
    Icm = 0

    # 依据密钥长度key_len确定分组个数
    un_cip = ['' for _ in range(key_len)]

    # 进行分组
    # 依据维吉尼亚密码加密的特性，每隔key_len个字符都是使用相同字母加密的
    # 使用数学形式表示为：模key_len相同字母使用同一字母加密
    for i in range(cipher_len):
        z = i % key_len
        un_cip[z] += cipher[i]
        
    # 计算每一个分组后的字符串的重合指数
    for i in range(key_len):
        # 统计频率
        N = [0 for _ in range(26)]
        for j in range(len(un_cip[i])):
            N[ord(un_cip[i][j]) - ord('A')] += 1
            
        # 计算并输出重合指数
        Icm1 = 0
        Icm2 = 0
        for j in range(0,26):
            Icm1 += (N[j] * (N[j]-1))
        Icm2 = Icm1 / (len(un_cip[i]) * (len(un_cip[i])-1))
        print(Icm2,end=" ")
        Icm += Icm2
    return Icm / key_len

def crack(cipher,key_len,cipher_len):
    un_cip = ['' for _ in range(key_len)]
    ans = ""
    for i in range(cipher_len):
        z = i % key_len
        un_cip[z] += cipher[i]
        
    for i in range(key_len):
        N = [0 for _ in range(26)]
        temp = [0 for _ in range(26)]
        for j in range(len(un_cip[i])):
            N[ord(un_cip[i][j]) - ord('A')] += 1
        
        for j in range(26):
            Mg = 0
            Mg1 = 0
            for k in range(26):
                Mg1 += N[k] * wf[(k-j)%26]
            Mg = Mg1 / len(un_cip[i])
            temp[j] += Mg
            print(chr(ord('A')+j),Mg,end=" ")
        ans += chr(temp.index(max(temp))+ord('A'))
        print()
    return ans

def main():
    # 写入字符串
    cipher = input()

    # 求取写入字符串的长度
    cipher_len = len(cipher)
    ans = ""
    for i in range(20):
        print(i + 1)
        temp = icm(cipher,i+1,cipher_len)
        if temp > 0.06:
            print()
            ans += crack(cipher,i+1,cipher_len)
            break
        print()
    print("密钥为：",ans)
    ClearText = vigenerecipher.decode(cipher,ans)
    print("密文解密为：",ClearText)
# 测试字符串：
# KCCPKBGUFDPHQTYAVINRRTMVGRKDNBVFDETDGILTXRGUDDKOTFMBPVGEGLTGCKQRACQCWDNAWCRXIZAKFTLEWRPTYCQKYVXCHKFTPONCQQRHJVAJUWETMCMSPKQDYHJVDAHCTRLSVSKCGCZQQDZXGSFRLSWCWSJTBHAFSIASPRJAHKJRJUMVGKMITZHEPDISPZLVLGWTFPLKKEBDPGCEBSHCTJRWXBAFSPEZQNRWXCVYCGAONWDDKACKAWBBIKFTIOVKCGGHJVLNHIFFSQESVYCLACNVRWBBIREPBBVFEXOSCDYGZWPFDTKFQIYCWHJVLNHIQIBTKHJVNPIST
# 密钥长度为6

# 测试字符串：
# CHREEVOAHMAERATBIAXXWTNXBEEOPHBSBQMQEQERBWRVXUOAKXAOSXXWEAHBWGJMMQMNKGRFVGXWTRZXWIAKLXFPSKAUTEMNDCMGTSXMXBTUIADNGMGPSRELXNJELXVRVPRTULHDNQWTWDTYGBPHXTFALJHASVBFXNGLLCHRZBWELEKMSJIKNBHWRJGNMGJSGLXFEYPHAGNRBIEQJTAMRVLCRREMNDGLXRRIMGNSNRWCHRQHAEYEVTAQEBBIPEEWEVKAKOEWADREMXMTBJJCHRTKDNVRZCHRCCQOHPWOAIIWXNRMGWOIIFKEE
# 密钥长度为5
if __name__ == '__main__':
    main()