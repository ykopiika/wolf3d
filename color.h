/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_text.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 18:41:09 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/07 18:41:13 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

#define T_BLK "\x1b[30m" // 30 - text is 	black
#define T_RED "\x1b[31m" // 31 - text is 	red
#define T_GRN "\x1b[32m" // 32 - text is 	green
#define T_YEL "\x1b[33m" // 33 - text is 	yellow
#define T_BLU "\x1b[34m" // 34 - text is 	blue
#define T_PNK "\x1b[35m" // 35 - text is 	pink
#define T_TRK "\x1b[36m" // 36 - text is 	turquoise

#define M_BLK "\x1b[40m" // 40 - black 		marker for text
#define M_RED "\x1b[41m" // 41 - red 		marker for text
#define M_GRN "\x1b[42m" // 42 - green		marker for text
#define M_YEL "\x1b[43m" // 43 - yellow		marker for text
#define M_BLU "\x1b[44m" // 44 - blue		marker for text
#define M_PNK "\x1b[45m" // 45 - pink		marker for text
#define M_TRK "\x1b[46m" // 46 - turquoise	marker for text

#define T_BLD "\x1b[1m"  //  1  bold 		text
#define T_CRS "\x1b[3m"  //  3  cursive 	text
#define T_UNL "\x1b[4m"  //  4  underline 	text
#define T_SLV "\x1b[2m"  //  2  text is 	silver

#define R "\x1B[0m"		 // reset

#endif


unsigned char i:1;

0000 0011 == 3
++++ ++++
0000 0110 == 6
==== ====
0000 1001
       2     10
0000 0000 == 0
0000 0001 == 1
0000 0010 == 2
0000 0011 == 3
0000 0100 == 4
0000 0101 == 5
0000 0110 == 6
0000 0111 == 7
0000 1000 == 8
0000 1001 == 9
0000 1010 == 10
0000 1011 == 11
0000 1100 == 12
0000 1101 == 13
0000 1110 == 14
0000 1111 == 15