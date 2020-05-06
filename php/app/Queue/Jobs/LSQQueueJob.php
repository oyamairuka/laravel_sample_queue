<?php

namespace App\Queue\Jobs;

use Illuminate\Container\Container;
use Illuminate\Queue\Jobs\Job;
use Illuminate\Contracts\Queue\Job as JobContract;

use App\Queue\LSQQueue;

class LSQQueueJob extends Job implements JobContract
{
    /**
     * The lsq queue instance.
     *
     * @var \App\Queue\LSQQueue
     */
    protected $lsq;

    /**
     * The lsq job payload.
     *
     * @var \stdClass
     */
    protected $job;

    /**
     * Create a new job instance.
     *
     * @param \Illuminate\Container\Container $container
     * @param \App\Queue\LSQQueue $lsq
     * @param \stdClass $job
     * @param string $connectionName
     * @param string $queue
     * @return void
     */
    public function __construct(Container $container, LSQQueue $lsq, $job, $connectionName, $queue)
    {
        $this->job = $job;
        $this->queue = $queue;
        $this->lsq = $lsq;
        $this->container = $container;
        $this->connectionName = $connectionName;
    }

    /**
     * Get the job identifier. 
     *
     * @return int
     */
    public function getJobId()
    {
        // TODO
        return 1;
    }

    /**
     * Get the number ob times the job has been attempted.
     *
     * @return int
     */
    public function attempts()
    {
        // TODO
        return 1;
    }

    /**
     * Get the raw body string for the job.
     *
     * @return string
     */
    public function getRawBody()
    {
        return $this->job->payload;
    }
}
