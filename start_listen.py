import subprocess
import time

def run_listener(num_processes):
    processes = []
    
    for i in range(num_processes):
        print(f"Starting listener process {i + 1}...")
        process = subprocess.Popen(["ros2", "run", "ros_speed", "listener",str(i)])
        processes.append(process)
        time.sleep(0.1)  # 可选：控制进程启动的间隔时间

    return processes

def main():
    num_processes = 32  # 启动8个进程
    processes = run_listener(num_processes)

    # 等待所有进程完成
    for process in processes:
        process.wait()
    
    print("All listener processes have finished.")

if __name__ == "__main__":
    main()

