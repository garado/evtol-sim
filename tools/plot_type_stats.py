import pandas as pd
import matplotlib.pyplot as plt
import sys
from io import StringIO

filename = sys.argv[1] if len(sys.argv) > 1 else 'output.csv'
df = pd.read_csv(filename)

fig, axes = plt.subplots(2, 3, figsize=(15, 10))

axes[0, 0].bar(df['VehicleType'], df['VehicleCount'])
axes[0, 0].set_title('Vehicle count')

axes[0, 1].bar(df['VehicleType'], df['FlightTimePerFlight(Hours)'])
axes[0, 1].set_title('Average flight time per flight (hours)')

axes[0, 2].bar(df['VehicleType'], df['DistPerFlight'])
axes[0, 2].set_title('Average distance per flight (miles)')

axes[1, 0].bar(df['VehicleType'], df['ChgSessionTime'])
axes[1, 0].set_title('Average charge session time (hours)')

axes[1, 1].bar(df['VehicleType'], df['TotalFaults'])
axes[1, 1].set_title('Total faults')

axes[1, 2].bar(df['VehicleType'], df['TotalPassengerMiles'])
axes[1, 2].set_title('Total passenger miles')

plt.tight_layout()
plt.show()
