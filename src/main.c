/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/17 15:06:28 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// utiliser fork() pour créer les processus enfants
// rediriger les descripteurs de fichiers avec dup2()
// exécuter ses commandes avec execve() dans les processus enfants.

int main(int argc, char **argv)
{
	t_data	data;
	if(argc > 4)
	{
		init_struct(argc, argv, &data);
		if(data.has_heredoc == TRUE)
			with_here_doc(&data);
		else 
			without_here_doc(&data);
	}
	else
		printf("wrong arguments number\n");
		return (0);
}

// ft_exec()
// {
// 	pipe()
// 	fork()
// 	if (child)
// 	{
// 		dup2()
// 		execve()
// 	}
// 	else
// 	{
// 		close()
// 	}
// }

    // Ouvrir file1 en mode lecture ("r") et file2 en mode écriture ("w").
    // Créer un tube (pipe) pour établir la communication entre les processus cmd1 et cmd2.
    // Utiliser fork() pour créer deux processus enfants, un pour cmd1 et l'autre pour cmd2.
    // Dans le processus enfant de cmd1, rediriger la sortie standard (stdout) vers 
	// l'extrémité de lecture du tube en utilisant dup2().
    // Dans le processus enfant de cmd2, rediriger l'entrée standard (stdin) depuis 
	// l'extrémité d'écriture du tube vers file2 en utilisant dup2().
    // Fermer les descripteurs de fichiers inutilisés dans chaque processus enfant.
    // Exécuter cmd1 et cmd2 respectivement dans chaque processus enfant en utilisant 
	// execve() ou une fonction similaire pour remplacer le code du processus enfant 
	// par celui de cmd1 ou cmd2.