import pandas as pd
import matplotlib.pyplot as plt
import sys

filename = sys.argv[1] if len(sys.argv) > 1 else 'mode_stats.csv'
df = pd.read_csv(filename)

# Group by vehicle type and calculate mean time in each mode
grouped = df.groupby('VehicleType')[['Idle', 'Wait_Chg', 'Chg_Done', 'Chg', 'Fly']].mean()

# Create stacked bar chart
fig, ax = plt.subplots(figsize=(10, 6))

grouped.plot(kind='bar', stacked=True, ax=ax, 
             color=['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#aa00bb'])

ax.set_title('Average Time Distribution by Vehicle Type')
ax.set_xlabel('Vehicle Type')
ax.set_ylabel('Proportion of Time')
ax.set_xticklabels(grouped.index, rotation=45)
ax.legend(title='Mode', labels=['Idle', 'Waiting to Charge', 'Charge Complete', 'Charge', 'Flying'])

plt.tight_layout()
plt.show()
