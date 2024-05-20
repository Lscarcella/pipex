/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:09:26 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/20 12:58:59 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// int main()
// {
//     const char *str1 = "hello";
//     const char *str2 = "hello";
//     const char *str3 = "hell";
//     const char *str4 = "world";

//     printf("Comparing '%s' and '%s': %d\n", str1, str2, ft_strcmp(str1, str2)); // Output: 0
//     printf("Comparing '%s' and '%s': %d\n", str1, str3, ft_strcmp(str1, str3)); // Output: positive value
//     printf("Comparing '%s' and '%s': %d\n", str1, str4, ft_strcmp(str1, str4)); // Output: negative value

//     return 0;
// }
