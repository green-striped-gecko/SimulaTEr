# SimulaTEr
A program to simulate capture-recapture histories under the TE (temporary emigration) model.

In the TE model individuals can be in two states (observable and unobservable). Individuals move with transition probabilities $\Psi_{OU}$ from the observable state to the unobservable state and $\Psi_{UO}$ from the unobservable state to the observable state. 

The transition matrix for the model is: 

$$
\left[ \begin{array}{cc}
1-\Psi_{OU} & \Psi_{OU} \\ 
\Psi_{UO} & 1-\Psi_{UO}
\end{array}\right]
\left[ \begin{array}{c}
S_O \\ 
S_U 
\end{array}\right]
\left[ \begin{array}{c}
p \\ 
0
\end{array}\right]
$$

 ,
where $S_O$ and $S_U$ are the probabilities that an individual survives in the observable respectively unobservable state during one time step and $p$ is the recapture probability in the observable state. 



Reference:

Henle & Gruber (accepted). Performance of multistate mark-recapture models for temporary emigration in the presence of survival costs. *Methods in Ecology and Evolution*