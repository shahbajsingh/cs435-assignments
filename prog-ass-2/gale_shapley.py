import random
import time
import matplotlib.pyplot as plt

def gen_prefs(n):
    return [random.sample(range(n), n) for _ in range(n)]

def gale_shapley(n, m_prefs, w_prefs):
    # inverse pref list for women
    w_prefs_inv = [{} for _ in range(n)]
    for w in range(n):
        for rank, m in enumerate(w_prefs[w]):
            w_prefs_inv[w][m] = rank

    # free (unmatched) men list
    free_m = list(range(n))

    # proposals made by men to women
    props = [0] * n

    # women's matches (-1 means unmatched)
    w_match_to = [-1] * n

    while free_m:
        man = free_m[0]
        w_pref = m_prefs[man][props[man]]
        props[man] += 1

        if (w_match_to[w_pref] == -1):
            w_match_to[w_pref] = man
            free_m.pop(0)
        else:
            curr_man = w_match_to[w_pref]
            if w_prefs_inv[w_pref][man] < w_prefs_inv[w_pref][curr_man]:
                w_match_to[w_pref] = man
                free_m[0] = curr_man

    matches = [(m, w_match_to.index(m)) for m in range(n)]
    # print formatted matches
    print("Matches:")
    for m, w in matches:
        print(f"{m} -> {w}")
    return matches

def validate(n, m_prefs, w_prefs, matches):
    woman_to_man = {w: m for m, w in matches}

    for m, w in matches:
        m_pref = m_prefs[m]
        w_pref = w_prefs[w]

        # check for any man this woman prefers more than her current partner
        for w2 in m_pref[:m_pref.index(w)]:
            m2 = woman_to_man[w2]
            if w_prefs[w2].index(m) < w_prefs[w2].index(m2):
                print(f'Unstable match: {w2} prefers {m} over {m2}')
                return False
            
        # check for any woman this man prefers more than his current partner
        for m2 in w_pref[:w_pref.index(m)]:
            w2 = woman_to_man[m2]
            if m_prefs[m2].index(w) < m_prefs[m2].index(w2):
                print(f'Unstable match: {m2} prefers {w} over {w2}')
                return False
        print(f'Match: {m} and {w} are stable')
    print("Matches are stable")
    return True


def main():
    input_sizes = [10, 100, 1000, 10000, 100000]
    times = []

    for n in input_sizes:
        m_prefs = gen_prefs(n)
        w_prefs = gen_prefs(n)

        start = time.time()
        matches = gale_shapley(n, m_prefs, w_prefs)
        end = time.time()
        times.append(end - start)

        if not validate(n, m_prefs, w_prefs, matches):
            print("Validation failed")
            return
        
    plt.plot(input_sizes, times, 'o-')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (s)')
    plt.title('Gale-Shapley Algorithm')
    plt.show()


if __name__ == "__main__":
    main()
