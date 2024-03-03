'''
Implementing the Gale-Shapley algorithm for stable matching of pairs, in this case with men and women, each with their own respective preferences.

The algorithm is implemented in the gale_shapley function, with helper functions gen_pref_list and val_stable, which generate random preference lists 
and validate the stability of the matching, respectively. The main function generates the preference lists, runs the algorithm, and validates the result.

For example, with men [A, B, C] and women [X, Y, Z], and the following preferences:

A: [X, Y, Z]    X: [B, A, C]
B: [Y, X, Z]    Y: [A, C, B]
C: [Z, X, Y]    Z: [A, B, C]

Say A proposes to X, his first choice, and X accepts. Then B proposes to Y, his first choice, and Y accepts. Finally, C proposes to Z, 
his first choice, and Z accepts. The result would be the stable matching [(A, X), (B, Y), (C, Z)]. This is stable because no two persons prefer
each other over their current partners. For example, A prefers X over Y, yet X prefers B over A, but B prefers Y over X. Likewise, C prefers Z over X and Y,
yet Z prefers A and even B over C, but A prefers X over Z. Therefore, no instability is found, and the matching is stable.

The Gale-Shapley algorithm is an efficient and guaranteed way to find a stable matching. It iterates through a list of unmatched men, and for each man,
it proposes to his next most preferred woman; if she is unmatched, they are engaged, otherwise, she compares her current partner with the proposer, and
if she prefers the proposer, she accepts him and rejects her current partner, who then becomes unmatched. This process continues until all men, and 
consequently all women, are matched. The result is guaranteed to be stable, as no two persons prefer each other over their current partners.
'''

import random  
import time
import matplotlib.pyplot as plt


def gen_rand_pref_list(n): 
    '''
    Generates a random preference list for n individuals.
    
    Parameters:
        n (int): The number of individuals.
        
    Returns:
        list: A list of preference lists, where each preference list represents the preferences of an individual.
    '''
    return [random.sample(range(n), n) for _ in range(n)] # Randomly sample n individuals without replacement, n times, to create n preference lists.

def gale_shapley(prefs_men, prefs_women):
    '''
    Runs the Gale-Shapley algorithm to find a stable matching of n pairs, given the preferences of a list of men and women.

    Parameters:
        n (int): The number of pairs.
        m_prefs (list): A list of preference lists, where each preference list represents the
        w_prefs (list): A list of preference lists, where each preference list represents the

    Returns:
        list: A list of engagements, where each engagement is a pair of individuals.
    '''
    n = len(prefs_men)
    if n != len(prefs_women):
        raise ValueError("ERROR: Length of preference lists must be equal.")
    
    unmatched_men = list(range(n))
    match_list_women = [-1] * n # -1 means unmatched
    match_list_men = [-1] * n # -1 means unmatched  

    while unmatched_men:
        man = unmatched_men[0]
        prefs_man = prefs_men[man]

        for woman in prefs_man:
            # if woman unmatched, match her with man
            if match_list_women[woman] == -1:
                match_list_women[woman] = man
                match_list_men[man] = woman
                unmatched_men.remove(man)
                print(f'Matched {man} with Preference {woman}')
                break
            # else woman is married, check if she prefers new man, if so, match her with new man and unmatch original man
            else:
                curr_man = match_list_women[woman]
                if prefs_women[woman].index(man) < prefs_women[woman].index(curr_man): # lower index --> higher preference
                    # unmatch curr_man 
                    unmatched_men.append(curr_man)
                    match_list_men[curr_man] = -1
                    # update match
                    match_list_women[woman] = man
                    match_list_men[man] = woman
                    unmatched_men.remove(man)
                    # print(f'Matched {man} with Preference {woman}')
                    # print(f'Unmatched {curr_man}')
                    break

    # return match list
    return [(m, w) for m, w in enumerate(match_list_men)]

def val_stable(match_list, prefs_men, prefs_women):
    '''
    Validates the stability of a matching, given the preferences of men and women.

    Parameters:
        match_list (list): A list of engagements, where each engagement is a pair of individuals
        prefs_men (list): A list of preference lists, where each preference list represents the preferences of that man
        prefs_women (list): A list of preference lists, where each preference list represents the preferences of that woman

    Returns:
        bool: True if the matching is stable, False otherwise.
        str: A message indicating whether the matching is stable or not.
    '''
    n = len(prefs_men)
    if n != len(prefs_women):
        raise ValueError("ERROR: Length of preference lists must be equal.")
    
    for m, w in match_list:
        m_pref = prefs_men[m]

        # check for instability against all other matches
        for m2, w2 in match_list:
            w_pref = prefs_women[w2]
            if m != m2 and w != w2: # if not same match
                # if man prefers other woman over his own AND other woman prefers man over her own
                # print(f'Comparing {m} with {m2} and {w} with {w2}')
                if m_pref.index(w2) < m_pref.index(w) and w_pref.index(m) < w_pref.index(m2):
                    # print preferences
                    print(f"Man {m}: {prefs_men[m]}"); print(f"Woman {w2}: {prefs_women[w2]}")
                    return False, f"Instability found: Man {m} and Woman {w2} prefer each other over their current partners."
                
    return True, "Stable matching confirmed"

def main():
    '''
    Generates random preference lists of sizes 10, 100, 1000 and runs the Gale-Shapley algorithm to find a stable matching for each size.
    '''

    # Generate preference lists
    input_sizes = [10, 100, 1000, 10000, 20000]
    exec_times = []
    val_stable_times = []

    for n in input_sizes:
        prefs_men = gen_rand_pref_list(n)
        prefs_women = gen_rand_pref_list(n)
        start_time = time.time()
        match_list = gale_shapley(prefs_men, prefs_women)
        exec_time = time.time() - start_time
        exec_times.append(exec_time)

        # Validate stability
        # start_time = time.time()
        # stable, message = val_stable(match_list, prefs_men, prefs_women)
        # val_stable_time = time.time() - start_time
        # val_stable_times.append(val_stable_time)
        print(f"n = {n}")
        print(f"Matching: {match_list}")
        # print(f"Stability: {message}")
        print(f"Execution time: {exec_time:.6f} seconds")
        # print(f"Validation time: {val_stable_time:.6f} seconds\n")

    # Plot execution times
    plt.plot(input_sizes, exec_times, marker='o')
    plt.title("Execution Time vs. Input Size")
    plt.xlabel("Input Size")
    plt.ylabel("Execution Time (seconds)")
    plt.show()

if __name__ == "__main__":
    main()
