import random
import time
import matplotlib.pyplot as plt

def generate_preferences(n):
    return [random.sample(range(n), n) for _ in range(n)]

def gale_shapley(n, men_preferences, women_preferences):
    women_inverse_pref = [{m: rank for rank, m in enumerate(women_preferences[w])} for w in range(n)]
    free_men = set(range(n))
    proposals = [0] * n
    women_engaged_to = [-1] * n
    
    while free_men:
        man = free_men.pop()
        woman = men_preferences[man][proposals[man]]
        proposals[man] += 1
        
        if women_engaged_to[woman] == -1:
            women_engaged_to[woman] = man
        else:
            current_partner = women_engaged_to[woman]
            if women_inverse_pref[woman][man] < women_inverse_pref[woman][current_partner]:
                women_engaged_to[woman] = man
                free_men.add(current_partner)
            else:
                free_men.add(man)
    
    engagements = [(man, women_engaged_to.index(man)) for man in range(n)]
    return engagements

def validate_stability(n, engagements, men_preferences, women_preferences):
    woman_to_man = {w: m for m, w in engagements}
    man_to_woman = {m: w for m, w in engagements}

    # Iterate through each woman to check her preferences
    for woman, her_current_man in woman_to_man.items():
        woman_pref = women_preferences[woman]
        # Check if there's any man she prefers more than the current one
        for preferred_man in woman_pref[:woman_pref.index(her_current_man)]:
            # Get the woman whom the preferred man is currently engaged to
            his_current_woman = man_to_woman[preferred_man]
            # Check if the preferred man would also prefer this woman over his current partner
            if men_preferences[preferred_man].index(woman) < men_preferences[preferred_man].index(his_current_woman):
                return False, f"Instability found: Woman {woman} prefers Man {preferred_man} over her current partner Man {her_current_man}, and Man {preferred_man} also prefers Woman {woman} over his current partner Woman {his_current_woman}"

    return True, "Stable matching confirmed"

# Example with n = 4
n = 100
men_preferences = generate_preferences(n)
women_preferences = generate_preferences(n)
engagements = gale_shapley(n, men_preferences, women_preferences)
stability, message = validate_stability(n, engagements, men_preferences, women_preferences)
print(f"Engagements: {engagements}")
print(f"Stability: {message}")
