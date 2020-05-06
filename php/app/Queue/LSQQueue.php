<?php

namespace App\Queue;

use Illuminate\Queue\Queue;
use Illuminate\Contracts\Queue\Queue as QueueContract;
use Http;
use Log;


use App\Queue\Jobs\LSQQueueJob;

class LSQQueue extends Queue implements QueueContract
{

    /**
     * The ip address of the host.
     *
     * @var string
     */
    protected $host;

    /**
     * The port of the laravel sample queue.
     *
     * @var int
     */
    protected $port;

    /**
     * The name of the default queue.
     *
     * @var string
     */
    protected $default;

    /**
     * Create a new laravel sample queue instance.
     *
     * @param string $host
     * @param int $port
     * @param string $default
     */
    public function __construct($host, $port, $default = 'default')
    {
        $this->host = $host;
        $this->port = $port;
        $this->default = $default;
    }

    /**
     * Get the size of the queue.
     *
     * @param string|null $queue
     * @return int
     */
    public function size($queue = null)
    {
        $response = Http::Post($this->getURL() . 'size', []);
        return intval($response->body());
    }

    /**
     * Push a new job onto the queue.
     *
     * @param string|object $job
     * @param mixed $data
     * @param string|null $queue
     * @return mixed
     */
    public function push($job, $data = '', $queue = null)
    {
        Log::debug(LSQQueue::class . '::push');
        $payload = $this->createPayload($job, $queue, $data);
        $response = $this->pushToQueue($this->getQueue($queue), $payload);
        if ($response->body() === '-1') {
            Log::error(LSQQueue::class . '::push' . ' FAILED');
        }
    }

    /**
     * Undocumented function
     *
     * @param string $payload
     * @param string|null $queue
     * @param array $options
     * @return mixed
     */
    public function pushRaw($payload, $queue = null, array $options = [])
    {
        Log::debug(LSQQueue::class . '::pushRaw');
        $response = $this->pushToQueue($this->getQueue($queue), $payload);
        if ($response->body() === '-1') {
            Log::error(LSQQueue::class . '::pushRaw' . ' FAILED');
        }
    }

    /**
     * Push a new job onto the queue after a delay.
     *
     * @param \DateTimeInterface|\DateInterval|int $delay
     * @param string|object $job
     * @param mixed $data
     * @param string|null $queue
     * @return mixed
     */
    public function later($delay, $job, $data = '', $queue = null)
    {
        Log::debug(LSQQueue::class . '::later');
        $payload = $this->createPayload($job, $queue, $data);
        $response = $this->pushToQueue($this->getQueue($queue), $payload, $delay);
        if ($response->body() === '-1') {
            Log::error(LSQQueue::class . '::later' . ' FAILED');
        }
    }

    /**
     * Pop the next job off of the queue.
     *
     * @param string $queue
     * @return \Illuminate\Contracts\Queue\Job|null
     */
    public function pop($queue = null)
    {
        Log::debug(LSQQueue::class . '::pop');
        $response = Http::asForm()->post($this->getURL() . 'pop', ['currentTime' => $this->currentTime()]);
        Log::debug('response body : ' . $response->body());
        if (!($response->body() === "")) {
            $job = json_decode($response->body());
            return new LSQQueueJob(
                $this->container,
                $this,
                $job,
                $this->connectionName,
                $queue
            );
        }
        return null;
    }

    /**
     * Push a raw payload to the LaravelSampleQueue with a given delay.
     *
     * @param  string|null  $queue
     * @param  string  $payload
     * @param  \DateTimeInterface|\DateInterval|int  $delay
     * @param  int  $attempts
     * @return mixed
     */
    protected function pushToQueue($queue, $payload, $delay = 0, $attempts = 0)
    {
        return Http::asForm()->post(
            $this->getURL() . 'push',
            $this->buildLSQElement($queue, $payload, $this->availableAt($delay), $attempts)
        );
    }

    /**
     * Create an array to insert for the given job.
     *
     * @param  string|null  $queue
     * @param  string  $payload
     * @param  int  $availableAt
     * @param  int  $attempts
     * @return array
     */
    protected function buildLSQElement($queue, $payload, $availableAt, $attempts = 0)
    {
        return [
            'queue' => $queue,
            'attempts' => $attempts,
            'reservedAt' => 0,
            'availableAt' => $availableAt,
            'createdAt' => $this->currentTime(),
            'payload' => $payload,
        ];
    }

    /**
     * Get the queue or return the default.
     *
     * @param  string|null  $queue
     * @return string
     */
    public function getQueue($queue)
    {
        return $queue ?: $this->default;
    }

    /**
     * Get the laravel sample queue url.
     *
     * @return string
     */
    public function getURL()
    {
        return 'http://' . $this->host . ':' . $this->port . '/lsq/';
    }
}
