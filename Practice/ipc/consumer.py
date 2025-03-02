import sys
from multiprocessing import shared_memory
import warnings

warnings.filterwarnings("ignore")

def main():
    shm_name = "OS_SHM"

    try:
        # Connect to the shared memory
        shm = shared_memory.SharedMemory(name=shm_name)
        print("Consumer: Connected to shared memory.")

        # Read data from shared memory
        message = bytes(shm.buf[:]).rstrip(b'\x00').decode('utf-8')
        print(f"Consumer: Read from shared memory: {message}")

        # Cleanup shared memory
        shm.close()
        print("Consumer: Shared memory closed.")
    except FileNotFoundError:
        print("Consumer: Shared memory not found.", file=sys.stderr)
    except Exception as e:
        print(f"Consumer: Error: {e}", file=sys.stderr)

if __name__ == "__main__":
    main()

