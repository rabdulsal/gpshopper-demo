//
//  GPDShoppingListViewController.m
//  GPShopper-iOS
//
//  Created by James Lee on 12/5/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDShoppingListViewController.h"
#import "TWTSideMenuViewController.h"
#import "GPDLoginViewController.h"
#import <GPShopper/GPShopper.h>

@interface GPDShoppingListViewController ()

@property (strong, nonatomic) SCShoppingList *shoppingList;
@property (readonly) NSArray *listItems;
@end

@implementation GPDShoppingListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    

    
    self.shoppingList = [SCShoppingList defaultList];
    
    [self.shoppingList addObserver:self forKeyPaths:@[@"localItems",
                                                      @"syncedItems",
                                                      @"dataState",
                                                      @"syncEnabled"]];
    self.tableView.tableFooterView = [UIView new];
    
//    template code for adding custom item
//        NSString *msg = @"Test Item3 Message";
//        SCShoppingListItemId *i = [[SCShoppingListItemId alloc] initWithText: msg];
//        
//        
//        SCShoppingListItemPrimaryUpdate *update = [[SCShoppingListItemPrimaryUpdate alloc]
//                                                   initWithItemId: i
//                                                   message: msg
//                                                   mslSupplemental: @{}
//                                                   state: SCShoppingListItemTypeDefault];
//        [self.shoppingList stageUpdate: update];
    
     self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)dealloc
{
    [self removeObserver:self forKeyPaths:@[@"localItems",
                                            @"syncedItems",
                                            @"dataState",
                                            @"syncEnabled"]];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.navigationController.navigationBar setTintColor:[UIColor darkGrayColor]];
    [self.navigationController.navigationBar setTranslucent:NO];
    [self.navigationController.navigationBar setBarTintColor:[UIColor colorWithWhite:0.95 alpha:1]];
    [self.navigationController.navigationBar setTitleTextAttributes:@{
                                                                      NSFontAttributeName:[UIFont fontWithName:@"OpenSans-Semibold" size:18.0],
                                                                      NSForegroundColorAttributeName:[UIColor darkGrayColor]}];
    
    UIBarButtonItem *openItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"menu_icon"]
                                                                 style:UIBarButtonItemStylePlain
                                                                target:self
                                                                action:@selector(openButtonPressed)];
    
    
    
    if (self.navigationController.viewControllers[0] == self) {
        self.navigationItem.leftBarButtonItem = openItem;
    }
    
    
    SCSession *currentSession = [SCSession defaultSession];
    if (!currentSession.exists && [self isMovingToParentViewController]) {
        
        GPDLoginViewController *vc = [GPDLoginViewController new];
        UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:vc];
        [self presentViewController:nav animated:YES completion:nil];
    } else {
        [self.shoppingList fetch];
    }
}

- (void)openButtonPressed
{
    [self.view endEditing:YES];
    [self.sideMenuViewController openMenuAnimated:YES completion:nil];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.shoppingList localItems].count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *reuseID = @"GPDShoppingListCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseID];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseID];
    }
    
    ShoppingListItem *item = [self.shoppingList.localItems allValues][indexPath.row];
    cell.textLabel.numberOfLines = 2;
    cell.textLabel.text = item.message;
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        ShoppingListItem *item = [self.shoppingList.localItems allValues][indexPath.row];
        SCShoppingListItemUpdate *update = [[SCShoppingListItemUpdate alloc] initWithItemId:[item newItemId] isDeletion:YES];
        [self.shoppingList stageUpdate:update];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        
    }
}

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    return NO;
}

/*
#pragma mark - Table view delegate

// In a xib-based application, navigation from a table can be handled in -tableView:didSelectRowAtIndexPath:
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    // Navigation logic may go here, for example:
    // Create the next view controller.
    <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:<#@"Nib name"#> bundle:nil];
    
    // Pass the selected object to the new view controller.
    
    // Push the view controller.
    [self.navigationController pushViewController:detailViewController animated:YES];
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ([keyPath isEqualToString:@"localItems"]) {
        NSIndexSet *indexSet = [NSIndexSet indexSetWithIndex:0];
        [self.tableView reloadSections:indexSet withRowAnimation:UITableViewRowAnimationAutomatic];
    } else if ([keyPath isEqualToString:@"syncedItems"]) {
        
    } else if ([keyPath isEqualToString:@"dataState"]) {
        
    } else if ([keyPath isEqualToString:@"syncEnabled"]) {
        
    }
}

@end
