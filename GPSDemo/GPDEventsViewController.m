//
//  GPDEventsViewController.m
//  GPSDemo
//
//  Created by James Lee on 10/9/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDEventsViewController.h"
#import "GPDEventsDetailViewController.h"
#import "GPDEventCell.h"
#import "GPDImageFetcher.h"

@interface GPDEventsViewController () {
    CGFloat _yPos;
    CGFloat _yDelta;
}

@property (strong, nonatomic) SCEventsFetcher *eventsFetcher;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NSArray *events;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *spinner;

@end

@implementation GPDEventsViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [super viewDidLoad];
    [self.tableView registerNib:[UINib nibWithNibName:@"GPDEventCell" bundle:nil]
         forCellReuseIdentifier:@"GPDEventCell"];
    self.tableView.rowHeight = [UIScreen mainScreen].bounds.size.width * 320.f/320.f;
    
    self.eventsFetcher = [[SCEventsFetcher alloc] init];
    self.eventsFetcher.listener = self;
    [self fetchEvents];
}

- (void)fetchEvents
{
    [self.spinner startAnimating];
    SCEventSearchSpecs *searchSpecs = [[SCEventSearchSpecs alloc] initWithQuery:nil
                                                                        minDate:[NSDate date]
                                                                        maxDate:nil
                                                                       latitude:-1.0
                                                                      longitude:-1.0
                                                                        eventid:0];
    [self.eventsFetcher fetchEventsWithSpecs:searchSpecs];
}


#pragma mark SCEventsFetcherListener

-(void)scEventsFetcher: (SCEventsFetcher *)f
         fetchedEvents: (NSArray *)es
              forSpecs: (SCEventSearchSpecs *)s
{
    self.events = es;
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView reloadData];
        [self.spinner stopAnimating];
    });

    
}

-(void)scEventsFetcher: (SCEventsFetcher *)f
fetchedNoEventsForSpecs: (SCEventSearchSpecs *)s
{
    
}

#pragma mark UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.events count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *reuseID = @"GPDEventCell";
    GPDEventCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseID];

    SCEvent * event = self.events[indexPath.row];
    UIImage *cachedImage = [[GPDImageFetcher sharedInstance] cachedImageForURL:event.imageUrl];
    
    if (cachedImage) {
        cell.eventImage.image = cachedImage;
        cell.eventImage.alpha = 1.0;
    } else {
        cell.eventImage.alpha = 0.0;
        if (tableView.dragging == NO && tableView.decelerating == NO) {
            [self loadImageURL:event.imageUrl forIndex:indexPath];
        }
    }
    
    cell.titleLabel.text = event.eventName;
    cell.descriptionLabel.text = [NSString stringWithFormat:@"%@\n%@", event.shortDescription, event.longDescription];
    
    return cell;
}

#pragma mark UITableViewDelegate : UIScrollViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    SCEvent *event = self.events[indexPath.row];
    GPDEventsDetailViewController *vc = [GPDEventsDetailViewController new];

    vc.event = event;
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    float velocity = _yPos - scrollView.contentOffset.y;
    _yPos = scrollView.contentOffset.y;
    _yDelta += velocity;
    
    if (fabsf(velocity) < 5 && abs(_yDelta) > 20) {
        [self loadImagesForOnscreenRows];
        _yDelta = 0;
    }
}

- (void)scrollViewDidEndDecelerating
{
    [self loadImagesForOnscreenRows];
}

- (void)loadImagesForOnscreenRows
{
    NSArray *visiblePaths = [self.tableView indexPathsForVisibleRows];
    
    for (NSIndexPath *indexPath in visiblePaths)
    {
        SCEvent *event = self.events[indexPath.row];
        
        UIImage *cachedImage = [[GPDImageFetcher sharedInstance] cachedImageForURL:event.imageUrl];
        if (!cachedImage) {
            [self loadImageURL:event.imageUrl forIndex:indexPath];
        }
    }
}

- (void)loadImageURL:(NSString *)url forIndex:(NSIndexPath *)indexPath
{
    // Check if product has url
    if (!url.length) {
        return;
    }
    
    [[GPDImageFetcher sharedInstance]
     fetchImageForURL:url
     cache:YES
     completion:^(UIImage *image) {
         if (image) {
             GPDEventCell *cell = (GPDEventCell *)[self.tableView cellForRowAtIndexPath:indexPath];
             dispatch_async(dispatch_get_main_queue(), ^{
                 cell.eventImage.image = image;
                 [UIView animateWithDuration:1.0 animations:^{
                     cell.eventImage.alpha = 1.0;
                 }];
             });
         }
     }];
}
@end
